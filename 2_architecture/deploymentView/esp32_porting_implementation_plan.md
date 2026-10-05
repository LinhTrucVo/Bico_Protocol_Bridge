# Temporary AI Implementation Instructions

> Temporary working instructions for implementing the hardware-independent software and device workspace architecture. This file is not part of the deployment architecture documentation.

## Scope

- Goal: complete the code generation and get `idf.py build` to pass for the ESP32 workspace.
- Out of scope: the template `_function1`, every `6_test` folder, the root `CMakeLists.txt`, `6_ut`, and any host or UT build. Do not run a host build.
- File names use camel case. Names and macros in device workspace use the prefix `bico_protocol_bridge` / `BICO_PROTOCOL_BRIDGE`.
- Work order: complete Phase 1 and Phase 2 for the ADC driver first, run the build (Verification), then repeat for the other 8 drivers.

## Phase 1 - Clean up `3_swComp`

This phase blocks Phase 2. Apply it to each of the 9 layer1 drivers.

1. Add `3_inc/<drv>Port.h`:
   - Standard C types only, common use function of the peripheral, no vendor peripheral specific, no vendor types
   - For each asynchronous event of the driver (ADC sample timer, GPIO interrupt, UART RX, I2C/SPI slave RX/TX, completion of master or NVM operations), add a handler registration, e.g. `AdcPort_SetSampleHandler(handler)`. The port only calls the registered handler. The generic driver owns the user callback.
2. Refactor `5_src/<drv>Unit.c`:
   - Move the driver logic (validation, state, callbacks, error mapping) out of `<drv>UnitEsp32.c` into the generic file.
   - Replace the `TODO: Add vendor-specific HAL` stubs with port calls.
   - Replace `memset_s` in `adcDriverUnit.c` with `memset`, because ESP-IDF does not provide `memset_s`.
3. Move `5_src/<drv>UnitEsp32.c` out of `3_swComp` and reduce it to a port implementation in device wworkspace `<drv>PortEsp32.c` (see Phase 2). Delete the original.
4. In each component `CMakeLists.txt`:
   - Replace the `# Add vendor HAL dependencies here` placeholder with `target_link_libraries(<drv> PUBLIC bico_protocol_bridge_port)`. The integrator supplies `bico_protocol_bridge_port`. ESP-IDF does not read these files.
   - Remove `add_subdirectory(6_test/gtest)`.
5. Add `3_swComp/bicoProtocolBridgeSwComp.cmake`, which exports `BICO_PROTOCOL_BRIDGE_SWCOMP_SOURCES` and `BICO_PROTOCOL_BRIDGE_SWCOMP_INCLUDE_DIRS`:
   - Paths are built from `CMAKE_CURRENT_LIST_DIR`.
   - It lists the `5_src/*.c` files and the `3_inc`, `4_config`, `5_src` include directories of the 9 drivers, the 9 services and `centralAppController`.
   - It excludes `_function1`, all `6_test` folders, and `4_addOn/addon1` (its prebuilt `libdebug_logging.a` is a host library).

## Phase 2 - Device workspace (ESP32 example)

This phase depends on Phase 1.

1. Rename `project(hello_world)` to `project(bico_protocol_bridge_esp32)`.
2. In the project `CMakeLists.txt`, before `include(project.cmake)`, set `EXTRA_COMPONENT_DIRS` to `main/bico_protocol_bridge_swcomp` and `main/bico_protocol_bridge_port_esp32`. ESP-IDF does not discover components inside `main/` otherwise.
3. `main/bico_protocol_bridge_swcomp/CMakeLists.txt` includes `bicoProtocolBridgeSwComp.cmake` and registers the sources with `idf_component_register`. It contains no copied source files.
4. `main/bico_protocol_bridge_port_esp32/`:
   - Contains the `<drv>PortEsp32.c` files.
   - `PRIV_REQUIRES esp_adc esp_driver_gpio esp_driver_uart esp_driver_i2c esp_driver_spi esp_driver_ledc nvs_flash esp_timer freertos`. It does not require `bico_protocol_bridge_swcomp`; the port headers come from the manifest include directories. `bico_protocol_bridge_swcomp` requires the port component instead, so the port is linked after the software.
   - `serialDriver` uses UART1 or UART2, never UART0 (used by the console and Arduino `Serial`).
5. Add one hardware configuration header per driver in `main/config/`, named `<drv>PortEsp32Cfg.h` (e.g. `adcPortEsp32Cfg.h`):
   - It defines the pins and related hardware settings as `BICO_PROTOCOL_BRIDGE_<DRV>_*` macros (pins, port/host number, baud rate, frequency, slave address, attenuation, ...), each wrapped in `#ifndef` so a project can override it.
   - The `<drv>PortEsp32.c` files take every pin and hardware setting from this header and contain no literal pin numbers.
   - Default values come from the `main.c` files in `D:\sandbox\esp32\esp32c3_test`:
     - `adcDriver`: `esp32_analog_test`
     - `gpioDriver`: `esp32_gpio_test`
     - `pwmDriver`: `esp32_pwm_test`
     - `serialDriver`: `esp32_uart_test`
     - `i2cMasterDriver` and `i2cSlaveDriver`: `esp32_i2c_test/esp_i2c_master` and `esp_i2c_slave`
     - `spiMasterDriver` and `spiSlaveDriver`: `esp32_spi_test/with_dma/esp_spi_master` and `esp_spi_slave`
     - `nvmDriver`: `esp32_storage_vfs_test`
   - Those tests target ESP32-C3. Check the `IDF_TARGET` of the workspace (its build cache shows `esp32`) and keep the pins valid for that target.
6. `main/main.cpp` calls `CentralAppControllerUnit_Init()` in `setup()` (it initializes the services and through them the drivers). `loop()` calls `ComServiceUnit_Run` and `CentralAppControllerUnit_Run`. Include the C headers inside `extern "C"`. `main/CMakeLists.txt` uses `REQUIRES bico_protocol_bridge_swcomp arduino`.
7. Set `CONFIG_I2C_ENABLE_SLAVE_DRIVER_VERSION_2=y` in `sdkconfig.defaults` and `sdkconfig`; the I2C slave port needs the request/receive events of that driver.

## Verification

1. Searching `3_swComp` for `#include .*(esp_|driver/|nvs|Arduino|freertos)` returns no match.
2. Delete the stale `build/` folder of the workspace (or run `idf.py fullclean`), because it still holds the old folder path.
3. Compile the ESP32 code:

   ```powershell
   cd "D:\sandbox\Bico_Protocol_Bridge\7_1_esp32_workspace\esp32_bico_protocol_bridge"; . "D:\vor5hc\.espressif\v5.4.3\esp-idf\export.ps1"; idf.py build
   ```

4. If a build error comes from the generated code, fix it and rebuild until the build passes.
