---
name: swe4-unit-verification
description: Use when a software unit in 3_1_swComp is new or changed and its GoogleTest unit tests in 6_test/gtest must be written or updated, including fakes of other components (fff) and HAL (port) fakes with JSON data (ASPICE SWE.4).
---

# SWE.4 Software Unit Verification

Read `AGENTS.md` first.

## Scope

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- Tests run on the host in the `bico_gtest_docker` image (GoogleTest 1.17, fff). No hardware.
- `3_2_thirdPartiesSwComp` is not unit tested.

## Inputs

- `3_1_swComp/<layer>/<comp>/1_swcReq`, `2_design/<comp>Comp.rst` (`swc`, `sw-if`, `sw-ifelement`: argument types, ranges, return values, restrictions), other `2_design` files (`sw_detail`, `sw_unit` IDs), `3_inc`, `4_config`, frozen at gate G3
- Do not read `5_src`: tests are written from the design, in parallel with the code, and must not copy its behaviour

## Outputs

| Path | Content |
|---|---|
| `6_test/gtest/test<Comp>.cpp` | Test cases |
| `6_test/gtest/fake/fake<Dep>.h/.c` | fff fakes of other components' APIs |
| `6_test/gtest/fake/fake<Drv>Port.cpp` | HAL fake (layer1 drivers only) |
| `6_test/gtest/fake/data/<Suite>_<Case>.json` | Expected HAL calls and injected return values |
| `6_test/gtest/CMakeLists.txt` | Test executable |
| `5_buildEnviroment/unitTestBuild/CMakeLists.txt` | `add_subdirectory` of the test (one line per component); shared file, edit only if LEADER granted it |

`<Suite>_<Case>_actual.json` is written by the test run and ignored by git.

## Fakes of other components (fff)

Every API from another component that the unit under test calls is faked with fff:

```c
// fake/fakeGpioDriver.h
#include "fff.h"
#include "gpioDriver.h"
DECLARE_FAKE_VALUE_FUNC(GpioDriver_Status_t, GpioDriverUnit_WritePin, GpioDriver_Pin_t, GpioDriver_State_t);

// fake/fakeGpioDriver.c
#include "fakeGpioDriver.h"
DEFINE_FAKE_VALUE_FUNC(GpioDriver_Status_t, GpioDriverUnit_WritePin, GpioDriver_Pin_t, GpioDriver_State_t);
```

- Add `DEFINE_FFF_GLOBALS;` once in `test<Comp>.cpp`.
- In `SetUp()`, call `RESET_FAKE(...)` for every fake and `FFF_RESET_HISTORY()`.
- Control the behaviour per test with `<fn>_fake.return_val`, `return_val_seq` or `custom_fake`; check calls with `<fn>_fake.call_count` and `arg<N>_val`.

## HAL (port) fake with JSON data (layer1 drivers)

The shared helper is `5_buildEnviroment/unitTestBuild/halFake/bpbHalFake.h` (library `bpbHalFake`, uses nlohmann/json).

1. One JSON file per test case, `fake/data/<Suite>_<Case>.json`. It lists, in call order, the expected HAL calls with their arguments, the value to return and optional output parameters:

   ```json
   {
     "calls": [
       { "function": "GpioPort_ConfigurePin", "args": { "pin": 8, "mode": 2, "pull": 0, "driveStrength": 2, "initialHigh": false }, "return": true },
       { "function": "GpioPort_Read", "args": { "pin": 8 }, "return": true, "out": { "high": true } }
     ]
   }
   ```

   Argument keys are the parameter names in `<drv>Porting.h`. Enums are written as their integer value. Pointers to input data are written as the pointed-to values (arrays as JSON arrays).

2. `fake/fake<Drv>Port.cpp` implements every function of `3_inc/<drv>Porting.h` by forwarding to the helper:

   ```cpp
   extern "C" {
   #include "gpioDriverPorting.h"
   }
   #include "bpbHalFake.h"

   bool GpioPort_Read(uint8_t pin, bool *pHigh)
   {
       const nlohmann::json &e = BpbHalFake::Call("GpioPort_Read", {{"pin", pin}});
       if ((pHigh != nullptr) && e.contains("out"))
       {
           *pHigh = e["out"].value("high", false);
       }
       return e.value("return", false);
   }
   ```

3. In the test fixture:

   ```cpp
   void SetUp() override    { BpbHalFake::Load(BPB_HAL_FAKE_DATA_DIR); }
   void TearDown() override { BpbHalFake::Save(); EXPECT_TRUE(BpbHalFake::Verify()); }
   ```

4. Each test checks two things: the parameters passed to the HAL (by `Verify()`, comparing actual with expected calls) and the value the unit returns after the injected HAL return value (by `EXPECT_EQ` in the test).

5. `6_test/gtest/CMakeLists.txt` links the helper and sets the data folder:

   ```cmake
   target_link_libraries(test<Comp> bpbHalFake)
   target_compile_definitions(test<Comp> PRIVATE GTESTING BPB_HAL_FAKE_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/fake/data")
   ```

## Test design

For every public function of the unit, cover:

- Normal behaviour for each `swc_req` in `1_swcReq`, through the `sw_detail` design item(s) that realize it.
- Input classes and boundary values derived from the types, ranges and restrictions in each argument's `sw-ifelement`, using the methods below.
- Invalid input (NULL pointer, out-of-range values, wrong state such as call before `Init`).
- Every error return of a dependency or the HAL (fake returns failure) and the resulting status.

### Common unit testing methods

Apply the following methods where relevant to the documented interface and detailed design. Derive expected results from the design, not from `5_src`. Only construct inputs that can be represented by the argument type and exercised without undefined behaviour in the host test.

1. **Equivalence Partitioning**

   Divide the input domain into equivalence classes expected to be processed in the same way. Select representative values from each valid and invalid class to reduce redundant test cases.

   Example: for an input accepted from 1 through 100, cover values below 1, values from 1 through 100, and values above 100.

2. **Boundary Value Analysis**

   Test values at and around the edges of input ranges, where defects commonly occur. Take each argument's limits from its `sw-ifelement`; cover the minimum, the maximum, their nearest in-range neighbours and one value outside each limit where representable. Include relevant zero-length and first/last pin cases.

   Example: for an input accepted from 1 through 100, test 0, 1, 2, 99, 100 and 101.

3. **Decision Table Testing**

   Represent combinations of conditions and their expected actions in a table. Test each relevant feasible combination when behaviour depends on several input conditions, including rejected requests and expected dependency calls or absence of calls.

   Example: a request is accepted only when the caller is authenticated and the system is in the required operating mode:

   | Authenticated | Required mode | Expected action |
   |---|---|---|
   | No | No | Reject |
   | No | Yes | Reject |
   | Yes | No | Reject |
   | Yes | Yes | Accept |

4. **State Transition Testing**

   Verify valid transitions, invalid transitions and relevant state-dependent behaviour in response to events or inputs. Establish the initial state, apply the event, and check the resulting state through observable behaviour, return values and dependency calls.

   Example: for a diagnostic access state machine, test `Locked -> Unlocked` after successful authentication, `Locked -> Locked` after failed authentication, and `Unlocked -> Locked` after a security timeout. Simulate time and dependency results with fakes rather than real delays.

5. **Error Guessing**

   Use experience, domain knowledge and likely failure modes to identify additional cases beyond the formal techniques. Consider NULL or otherwise invalid pointers where safely testable, empty or unexpectedly large buffers, invalid enumerated values, repeated requests, unexpected call order, timeouts, interrupted operations and resource exhaustion. Use fakes to inject dependency failures; do not dereference arbitrary invalid pointers or pass buffers smaller than the size claimed by the test.

Test names: `TEST_F(<Comp>Test, <Function>_<Condition>_<ExpectedResult>)`.

## Traceability

```rst
.. sw_unit_test:: GpioDriver ConfigurePin tests
   :id: SWUT_GPIODRIVER_CONFIGUREPIN
   :verifies: SWDD_GPIODRIVER_CONFIGUREPIN, SWIFE_GPIODRIVER_CONFIGUREPIN
   :verification_result: passed
```

- Written in `6_test/gtest/index.rst` (create it and add it to the component `index.rst` toctree).
- `:verifies:` links to the `sw_detail` (detailed design) and `sw-ifelement` (interface design) items the tests check, not to the `sw_unit`.
- Tests do not link directly to `swc_req` or `sw_req`; verifying the design items that realize a `swc_req` verifies that component requirement.
- `:verification_result:` is one of `not_run`, `passed`, `failed`, `blocked`, `not_applicable`.

## Done criteria

- Every `sw_detail` and every `sw-ifelement` is verified by at least one `sw_unit_test`; each `swc_req` is covered through its realized design item(s).
- `5_buildEnviroment/unitTestBuild/unitTestBuild.sh` passes all tests. Line and branch coverage of the changed unit in `_build/unitTestBuild` are at least 90 % and are reported.
- `5_buildEnviroment/docGen/docGen.sh` builds without new warnings.
