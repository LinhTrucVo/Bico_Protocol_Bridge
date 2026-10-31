# Plan: Rework AGENTS.md and ASPICE skills (SWE.1-SWE.6)

Agents work only above the HAL. Each software component declares its own HAL (port) API.
Hardware workspaces implement it. Agents never read or write `7_1_esp32_workspace`.

## Decisions

| Topic | Decision |
|---|---|
| HAL boundary | Each layer1 driver declares `3_inc/<drv>Porting.h` (`<Drv>Port_*`, standard C types). Implementation is done by a separate agent in each hardware workspace `7_x_*`. |
| `7_1_esp32_workspace` | Do not read or write. Stated in AGENTS.md and every skill. |
| Skill structure | 6 skills, one per SWE.1-SWE.6 |
| Skill location | Keep `.agents/instruction/`, add YAML frontmatter, skill table in AGENTS.md |
| Traceability | Sphinx-Needs types/links from `5_buildEnviroment/docGen/aspice_config.py` for new or changed artefacts. Existing text not migrated. |
| Fakes of other components | fff (Fake Function Framework, in bico_gtest_docker image) |
| HAL fakes | JSON per test case, expected and actual under `<comp>/6_test/gtest/fake/data/`. Parsed with nlohmann/json via CMake FetchContent in `5_buildEnviroment/unitTestBuild`. |
| `esp32_porting_implementation_plan.md` | Delete (only this file in deploymentView) |
| Variant Handling in driver `1_swcReq` | Remove. Driver is hardware independent; HAL implementation follows `<drv>Porting.h`. |
| Ticket | Use existing `0_ticket/ticket_template.rst` |
| SWE.6 | Skill + README structure only, no tests until a ticket asks |
| READMEs | Fix stale paths |

## Phase A - AGENTS.md

- [x] A1 Rewrite `AGENTS.md`: purpose, repository map, 7_1 rule, HAL boundary, skill table (SWE step, skill, inputs, outputs, need type, link), global conventions (`BPB_` prefix, layer direction, component template, cmake registration, third-party exclusion), verify commands, change rule.

## Phase B - Skills in `.agents/instruction/`

Common layout: frontmatter (`name`, `description`), Inputs, Outputs, Steps, Traceability, Done criteria, scope rule (no 7_1, no hardware code).

- [x] B1 `1_requirement_analyzer` (SWE.1): `0_ticket` -> `1_requirement/<Feature>/`, ISO 29148, `sw_req`.
- [x] B2 `2_architecture_design` (SWE.2): `1_requirement` -> `2_architecture/`, ISO 42010, `sw_arch` `:realizes:`.
- [x] B3 `3_detailed_design_unit_construction` (SWE.3): -> `3_1_swComp/<layer>/<comp>/`, declare `3_inc/<drv>Porting.h`, register cmake, `sw_detail` `:refines:`, `sw_unit` `:implements:`.
- [x] B4 `4_unit_verification` (SWE.4): fff for other components, HAL JSON fake, `sw_unit_test` `:verifies:`.
- [x] B5 `5_integration_test` (SWE.5): -> `4_1_integrationTest/gtest/`, 5 criteria, `sw_integration_test` `:verifies:`.
- [x] B6 `6_qualification_test` (SWE.6): blocked until HIL environment exists; skill tells the agent to stop.
- [x] B7 Remove old `3_sw_component_preparation` and `4_testing`.

## Phase C - Repository alignment

- [x] C1 Move 9 `5_src/<drv>Porting.h` -> `3_inc/<drv>Porting.h` (git mv).
- [x] C2 Replace Variant Handling in 9 driver `1_swcReq/*Req.rst`.
- [x] C3 Delete `2_architecture/deploymentView/esp32_porting_implementation_plan.md`.
- [x] C4 Fix folder layout text in `2_architecture/deploymentView/index.rst`.
- [x] C5 Ticket template: user already added `0_ticket/ticket_template.rst`; AGENTS.md and SWE.1 reference it (no new file).
- [x] C6 Add `*_actual.json` to `.gitignore`.
- [x] C7 Add nlohmann/json FetchContent to `5_buildEnviroment/unitTestBuild/CMakeLists.txt`.
- [x] C8 Fix stale paths in `README.md` and `5_buildEnviroment/README.md`.
- [x] C9 Create shared HAL fake helper `5_buildEnviroment/unitTestBuild/halFake/` (load expected JSON, inject return values, record actual calls, write `_actual.json`, verify).

## Phase D - Verification

- [x] D1 Grep `.agents/**`, `AGENTS.md` for stale paths (`2_architecture_design/` as output, `3_sw_component_preparation`, `3_swComp/`, `4_addOn`).
- [x] D2 Grep `.agents/**` for `7_1`: only in the "do not read or write" rule.
- [x] D3 No `*Porting.h` in `3_1_swComp/**/5_src`; 9 in `3_inc`.
- [x] D4 get_errors on changed files (clean). Still to run: CI `unitTestBuild.sh` and `docGen.sh`; `idf.py build` by the user.
