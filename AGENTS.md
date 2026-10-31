# Bico Protocol Bridge - Agent Instructions

## Purpose

The device receives commands over a serial interface and controls peripherals (Analog, Digital I/O, PWM, I2C, SPI, NVM).
Development follows ASPICE 4.0 SWE.1 to SWE.6. Each SWE step has specific **instruction** in `.agents/instruction/`.
The tools that build the work products are in `5_buildEnviroment`.

## Scope rules

1. **Do not read or write `7_1_esp32_workspace`** (or any `7_x_*` hardware workspace). Each has its own agent and instructions.
2. **Work only above the HAL.** All software in `3_1_swComp` is hardware independent. No vendor header (`esp_*`, `driver/*`, `Arduino.h`, `freertos/*`, `stm32*`, ...) is included anywhere.
3. **Each layer1 driver declares its own HAL (port) API** in `3_inc/<drv>Porting.h`: `<Drv>Port_*` functions using standard C types only (for GPIO: init/configure, read, write, toggle, ...). Hardware workspaces implement this declaration; do not write the implementation.
4. Read-only: `3_2_thirdPartiesSwComp`, git submodules (`5_buildEnviroment/**/bico_*_docker`), `_build` (generated output).

## Repository map

| Folder | Content | Produced by |
|---|---|---|
| `0_ticket/` | Change requests `<yymmdd>_<hhmmss>.rst`, format in `0_ticket/ticket_template.rst`. Deleted after the implementation is done (ask the user first). | User |
| `1_requirement/<Feature>/` | Software requirements | SWE.1 |
| `2_architecture/` | Software architecture (`fucntionView`, `deploymentView`) | SWE.2 |
| `3_1_swComp/<layer>/<comp>/` | Detailed design, code, unit tests | SWE.3, SWE.4 |
| `3_2_thirdPartiesSwComp/` | Third-party components (read-only, no unit test) | - |
| `4_1_integrationTest/` | Software integration tests | SWE.5 |
| `4_2_qualificationTest/` | Software qualification tests | SWE.6 |
| `5_buildEnviroment/` | Doc generation, unit test build, Sphinx-Needs config | - |
| `7_x_*_workspace/` | Hardware workspaces (out of scope) | Separate agent |
| `_build/` | Generated output (never edit) | Build scripts |

## Skills

Read the skill of the step before starting it. Traceability uses the Sphinx-Needs types and links defined in `5_buildEnviroment/docGen/aspice_config.py`.

| Step | Skill | Input | Output | Need type | Link |
|---|---|---|---|---|---|
| SWE.1 | `.agents/instruction/1_requirement_analyzer/instructions.md` | `0_ticket` | `1_requirement` | `sw_req` | - |
| SWE.2 | `.agents/instruction/2_architecture_design/instructions.md` | `1_requirement` | `2_architecture` | `sw_arch` | `realizes` -> `sw_req` |
| SWE.3 | `.agents/instruction/3_detailed_design_unit_construction/instructions.md` | `1_requirement`, `2_architecture` | `3_1_swComp/<comp>/1_swcReq..5_src` | `sw_detail`, `sw_unit` | `refines` -> `sw_arch`, `implements` -> `sw_detail` |
| SWE.4 | `.agents/instruction/4_unit_verification/instructions.md` | `3_1_swComp/<comp>` | `3_1_swComp/<comp>/6_test/gtest` | `sw_unit_test` | `verifies` -> `sw_unit` |
| SWE.5 | `.agents/instruction/5_integration_test/instructions.md` | `2_architecture`, `3_1_swComp/<comp>/2_design` | `4_1_integrationTest` | `sw_integration_test` | `verifies` -> `sw_arch` |
| SWE.6 | `.agents/instruction/6_qualification_test/instructions.md` | `1_requirement` | `4_2_qualificationTest` | `sw_qualification_test` | `verifies` -> `sw_req` |

## Conventions

- **Prefix:** every macro and enum value starts with `BPB_` (avoids clashes with vendor SDKs).
- **Layers:** `layer3Application` -> `layer2Service` -> `layer1Driver` -> `<Drv>Port_*`. A layer calls only the layer directly below, through its `3_inc` header.
- **Component template:** `1_swcReq/`, `2_design/`, `3_inc/`, `4_config/`, `5_src/`, `6_test/gtest/{fake,mock,stub}/`, `7_tools/`, `8_misc/`, `CMakeLists.txt`, `index.rst`.
- **File names:** public API `3_inc/<comp>.h`, HAL API `3_inc/<drv>Porting.h`, configuration `4_config/<comp>Cfg.h`, implementation `5_src/<comp>Unit.c/.h`.
- **Registration:** a new component is added to `3_1_swComp/bicoProtocolBridgeSwComp.cmake` and its unit test to `5_buildEnviroment/unitTestBuild/CMakeLists.txt`.
- **Documentation:** reStructuredText and PlantUML; each new folder has an `index.rst` included in its parent toctree.
- **Change rule:** when an artefact changes, update the linked downstream artefacts (architecture, design, code, tests) in the same task.

## Verification

Both scripts run in Docker (Linux) and in CI (`.github/workflows/ci.yml`), from the repository root:

- Documentation: `5_buildEnviroment/docGen/docGen.sh` -> `_build/docGen`. No new Sphinx-Needs warnings.
- Unit tests and coverage: `5_buildEnviroment/unitTestBuild/unitTestBuild.sh` -> `_build/unitTestBuild`. No test failed and coverage should over 90%