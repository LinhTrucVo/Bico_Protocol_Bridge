# Temporary AI Implementation Instructions

> Temporary working instructions for implementing the hardware-independent software and device workspace architecture. This file is not part of the deployment architecture documentation.

## Phase 1 - Clean up `3_swComp`

This phase blocks all other phases. The 9 drivers can be handled in parallel.

1. Add `3_inc/<drv>Port.h` to every layer1 driver. It declares the minimal low level functions, e.g. `AdcPort_Init`, `AdcPort_ConfigChannel`, `AdcPort_ReadRaw`, `AdcPort_GetTimeUs`.
2. Refactor `5_src/<drv>Unit.c`: replace the `TODO: Add vendor-specific HAL` stubs with port calls and keep the generic logic.
3. Move `5_src/<drv>UnitEsp32.c` out of `3_swComp` and reduce each file to a port implementation `<drv>PortEsp32.c`. See Phase 3.
4. In each component `CMakeLists.txt`, replace the `# Add vendor HAL dependencies here` placeholder with the port dependency, and guard `add_subdirectory(6_test/gtest)` with `if(BICO_BUILD_TESTS)`.
5. Add a fake port per driver under `6_test/gtest/fake/` so that the unit tests link on the host.
6. Add `3_swComp/bicoSwComp.cmake`, which exports `BICO_SWCOMP_SOURCES` and `BICO_SWCOMP_INCLUDE_DIRS`.

## Phase 2 - Host build

This phase depends on Phase 1.

1. Fix the root `CMakeLists.txt`: remove the directories that do not exist (`ANALOGAPP`, `DIGITALAPP`, `I2CAPP`, `SPIAPP`, `function1/comp1`) and add the missing services (analogService, comService, digitalService, i2cService, spiService).
2. Enable `BICO_BUILD_TESTS=ON` for the host build and provide googletest, e.g. via `FetchContent`.

## Phase 3 - Device workspace (ESP32 example)

This phase depends on Phase 1 and can run in parallel with Phase 2.

1. `main/bico_protocol_bridge_swcomp/CMakeLists.txt` includes `bicoSwComp.cmake` and registers the sources with `idf_component_register`. It contains no copied source files.
2. `main/bico_protocol_bridge_port_esp32/` contains the `<drv>PortEsp32.c` files and requires `esp_adc`, `esp_driver_*`, `nvs_flash` and `esp_timer`.
3. `main/main.cpp` initializes all components in `setup()` in dependency order. `loop()` calls `ComService_Run` and `CentralAppController_Run`. Include the C headers inside `extern "C"`.
4. Rename `project(hello_world)` to `project(bico_bridge_esp32)`.

## Phase 4 - Keep it clean

This phase depends on Phase 3.

1. Support configuration overrides through `7_1_esp32_workspace/<project>/main/config/`.
2. Add a CI check that fails if any vendor header is included under `3_swComp`.

## Verification

1. Searching `3_swComp` for `#include .*(esp_|driver/|nvs|Arduino|freertos|stm32)` returns no match.
2. The host build with `BICO_BUILD_TESTS=ON` passes `ctest` using the fake ports only.
3. `idf.py build` succeeds in `7_1_esp32_workspace`, and `idf.py size-components` lists `bico_protocol_bridge_swcomp` and `bico_protocol_bridge_port_esp32`.
4. On the target, a request such as `CAC_RID_GPIO_WRITE` sent over serial toggles the pin and returns a valid response frame.
5. Adding `7_2_stm32_workspace` requires a new port and new glue only. `3_swComp` stays unchanged.

## Considerations

- The Arduino component pulls in about 21 managed components (rainmaker, zigbee, ...). Trimming them via `sdkconfig` reduces build time and binary size.
- If a port interface grows close to the full driver API, move that logic back into the generic driver.
- An RTOS abstraction (`osPort.h`) can be added the same way if the generic code needs mutexes or delays.
