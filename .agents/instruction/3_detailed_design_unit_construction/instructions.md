---
name: swe3-detailed-design-unit-construction
description: Use when the architecture in 2_architecture is new or changed and a software component in 3_1_swComp must be designed or coded - component requirements, detailed design, HAL (port) API declaration and C source (ASPICE SWE.3).
---

# SWE.3 Software Detailed Design and Unit Construction

Read `AGENTS.md` first. Unit tests are written with the SWE.4 skill (`.agents/instruction/4_unit_verification/instructions.md`).

## Scope

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- Code is hardware independent: no vendor header (`esp_*`, `driver/*`, `Arduino.h`, `freertos/*`, `stm32*`, ...), no register access, no `#ifdef` per target.
- A layer1 driver reaches the hardware only through the HAL (port) API it declares itself. Write the declaration, never the implementation; hardware workspaces implement it.
- `3_2_thirdPartiesSwComp` is read-only.

## Inputs

- `1_requirement/<Feature>/index.rst` (`sw_req`)
- `2_architecture/fucntionView/<layer>/<comp>/` (`sw_arch`)
- Existing `3_1_swComp/<layer>/<comp>/`

## Outputs

In `3_1_swComp/<layer>/<comp>/` (`<layer>` is `layer1Driver`, `layer2Service` or `layer3Application`):

| Path | Content |
|---|---|
| `1_swcReq/<comp>Req.rst` | Component requirements: interface, constraints, error behaviour |
| `2_design/<comp>Comp.rst`, `<comp>Unit.rst`, `<comp>Cfg.rst` | Detailed design (`sw_detail`) |
| `2_design/<comp>StaticStructure.puml`, `<comp>StateMachine.puml`, `<comp>SequenceDiagram.puml` | Design diagrams |
| `3_inc/<comp>.h` | Public API for the layer above |
| `3_inc/<drv>Porting.h` | HAL (port) API, layer1 drivers only |
| `4_config/<comp>Cfg.h` | Default configuration (may be overridden by a hardware workspace) |
| `5_src/<comp>Unit.c`, `5_src/<comp>Unit.h` | Implementation (`sw_unit`) |
| `CMakeLists.txt`, `index.rst` | Library target, documentation entry |

A new component also creates `6_test/gtest/{fake,mock,stub}/`, `7_tools/index.rst`, `8_misc/index.rst`, is added to `3_1_swComp/bicoProtocolBridgeSwComp.cmake` and to the toctree in `3_1_swComp/index.rst`.

## HAL (port) API rules (layer1 drivers)

1. Declared in `3_inc/<drv>Porting.h`, functions named `<Drv>Port_<Action>` (e.g. `GpioPort_Init`, `GpioPort_ConfigurePin`, `GpioPort_Read`, `GpioPort_Write`, `GpioPort_Toggle`).
2. Only standard C types (`stdint.h`, `stdbool.h`) and enums/structs declared in the same header.
3. Minimal and generic: the smallest set of operations every target can provide. Parameter checks, state, buffering and callback dispatch stay in `<drv>Unit.c`.
4. Every function returns a status (`bool` or a `BPB_` enum) unless it cannot fail.
5. Callbacks that may run in interrupt context are documented as such in a one-line comment.
6. A change to `<drv>Porting.h` is an interface change for every hardware workspace: state it in the answer to the user.

## Coding rules

- Every macro and enum value starts with `BPB_`. Include guards: `BPB_<FILE>_H`.
- A layer includes only `3_inc` headers of the layer directly below.
- No dynamic memory allocation. Static buffers sized by `4_config` macros.
- Public functions validate pointers and ranges and return an error status instead of crashing.

## Steps

1. List the `sw_arch` items that are new or changed and the components that refine them.
2. Update `1_swcReq/<comp>Req.rst` (interface, constraints, error codes).
3. Update `2_design` (`sw_detail`): units, data types, state machine, sequence for every public function.
4. Update headers (`3_inc`, `4_config`), then `5_src`.
5. Register a new component (`bicoProtocolBridgeSwComp.cmake`, toctree).
6. Continue with SWE.4 for the unit tests of the changed units.

## Traceability

```rst
.. sw_detail:: GPIO driver pin configuration
   :id: SWDD_GPIODRIVER_CONFIGUREPIN
   :refines: SWARCH_GPIODRIVER

.. sw_unit:: gpioDriverUnit
   :id: SWUNIT_GPIODRIVER
   :implements: SWDD_GPIODRIVER_CONFIGUREPIN
```

- `sw_detail` IDs: `SWDD_<COMP>_<ITEM>`, each with `:refines:` to a `sw_arch`.
- `sw_unit` IDs: `SWUNIT_<COMP>`, one per `5_src/<comp>Unit.c`, with `:implements:` to its `sw_detail` items.
- The directives `swc::`, `sw-if::`, `sw-ifelement::` in existing files are not defined in `aspice_config.py`. Replace them with `sw_detail` when the file is changed.

## Done criteria

- Every changed `sw_arch` is refined by at least one `sw_detail`, every `sw_detail` is implemented by a `sw_unit`.
- No vendor header in `3_1_swComp`: `grep -rE "esp_|driver/|Arduino.h|freertos/|stm32" 3_1_swComp --include=*.[ch]` returns nothing.
- `5_buildEnviroment/docGen/docGen.sh` builds without new warnings.
- `5_buildEnviroment/unitTestBuild/unitTestBuild.sh` compiles.
