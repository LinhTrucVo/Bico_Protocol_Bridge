---
name: swe5-integration-test
description: Use when components in 3_1_swComp are new or changed and their interaction must be verified against the architecture with GoogleTest integration tests in 4_1_integrationTest (ASPICE SWE.5).
---

# SWE.5 Software Integration and Integration Test

Read `AGENTS.md` first. The fake rules are those of SWE.4 (`.agents/instruction/4_unit_verification/instructions.md`).

## Scope

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- Integrate the real sources of all components listed in `3_1_swComp/bicoProtocolBridgeSwComp.cmake`. Only the HAL (`<Drv>Port_*`) is faked.
- Tests run on the host in the `bico_gtest_docker` image.

## Inputs

- `2_architecture/fucntionView/` (`sw_arch`: interfaces, information flow, dynamic behaviour)
- `3_1_swComp/<layer>/<comp>/2_design` and `3_inc`
- HAL fakes `3_1_swComp/layer1Driver/<drv>/6_test/gtest/fake/fake<Drv>Port.cpp`

## Outputs

| Path | Content |
|---|---|
| `4_1_integrationTest/gtest/integrationTest<Scope>.cpp` | Test cases, one file per architecture scope (e.g. `SerialToDigital`) |
| `4_1_integrationTest/gtest/data/<Suite>_<Case>.json` | Expected HAL calls and injected return values (SWE.4 JSON format) |
| `4_1_integrationTest/gtest/CMakeLists.txt` | Test executable |
| `4_1_integrationTest/index.rst` | `sw_integration_test` needs; add `../../4_1_integrationTest/index` to the toctree in `5_buildEnviroment/docGen/index.rst` if missing |
| `5_buildEnviroment/unitTestBuild/CMakeLists.txt` | `add_subdirectory` of `4_1_integrationTest/gtest` |

## Build

```cmake
include(${CMAKE_CURRENT_SOURCE_DIR}/../../3_1_swComp/bicoProtocolBridgeSwComp.cmake)
add_executable(integrationTest
    ${BICO_PROTOCOL_BRIDGE_SWCOMP_SOURCES}
    <test files and fake<Drv>Port.cpp of every driver>
)
target_include_directories(integrationTest PUBLIC ${BICO_PROTOCOL_BRIDGE_SWCOMP_INCLUDE_DIRS})
target_link_libraries(integrationTest bpbHalFake)
target_compile_definitions(integrationTest PRIVATE GTESTING BPB_HAL_FAKE_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")
```

## Criteria

Each test case covers at least one criterion and names it in the `sw_integration_test` description:

| # | Criterion | What is checked |
|---|---|---|
| 1 | Interface compatibility | Components communicate using the correct interfaces, APIs and protocols. |
| 2 | Data exchange | Data passes between components without corruption, loss or unexpected change. |
| 3 | Functional behaviour | Integrated components produce the expected result for each use case. |
| 4 | Interaction sequence | Operations run in the correct order and follow the expected state transitions. |
| 5 | Error handling | Errors, invalid input, timeouts and communication failures are handled correctly. |

## Steps

1. For each changed `sw_arch`, take the information flow and dynamic behaviour diagrams as test scenarios.
2. Drive the scenario from the highest affected layer (normally a serial command into `layer3Application`) and observe the result at the HAL fake (`BpbHalFake::Verify()`) and at the public API.
3. Inject HAL failures through the JSON `return` values to cover criterion 5.

## Traceability

```rst
.. sw_integration_test:: Digital write from serial command
   :id: SWIT_SERIALTODIGITAL_WRITE
   :verifies: SWARCH_CENTRALAPPCONTROLLER, SWARCH_DIGITALSERVICE, SWARCH_GPIODRIVER
   :verification_result: passed

   Criteria 1, 2, 3, 4.
```

## Done criteria

- Every changed `sw_arch` is verified by at least one `sw_integration_test`.
- `5_buildEnviroment/unitTestBuild/unitTestBuild.sh` passes all tests.
- `5_buildEnviroment/docGen/docGen.sh` builds without new warnings.
