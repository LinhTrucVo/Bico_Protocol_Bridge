Deployment View
###############

.. What is the Deployment View:
.. How the hardware independent software in 3_swComp is integrated into a hardware specific device workspace.

The software in ``3_swComp`` is **hardware independent**. It is deployed to a concrete device by a
**device workspace** ``7_x_<platform>_workspace``, which collects the ``3_swComp`` sources for the
build and adds everything that depends on the hardware.

- ``7_1_esp32_workspace``: ESP32 (ESP-IDF + Arduino), used as the example in this document
- ``7_2_stm32_workspace``: STM32 (future)
- ``7_n_<platform>_workspace``: further platforms follow the same pattern

Principles
**********

#. ``3_swComp`` contains no hardware dependent code. No vendor header (``esp_*``, ``driver/*``,
   ``nvs*``, ``Arduino.h``, ``freertos/*``, ``stm32*``) is included anywhere in ``3_swComp``.
#. Each layer1 driver is split into a **generic driver** (in ``3_swComp``) and a **port** (in the
   device workspace). The generic driver owns parameter checks, state handling, buffering and callback
   dispatch. It calls a small port interface ``xxxPort.h`` (3-6 functions, standard C types only).
#. The device workspace **compiles the 3_swComp sources in place** and never copies them. There is a single source of truth.
#. Exactly one port implementation is linked per build: the ESP32 port, the STM32 port or the fake port
   for host unit tests.
#. Default configuration lives in ``3_swComp/<comp>/4_config``. A device workspace may override it
   by placing its own ``xxxCfg.h`` earlier in the include path.

Overview
********
.. Relation between 3_swComp, the device workspaces and the host unit test build

..  uml:: deploymentOverview.puml

Port interface
**************
.. How one generic driver is served by several platform specific ports (adcDriver as example)

..  uml:: portInterface.puml

Build integration
*****************
.. How the ESP32 workspace collects 3_swComp for the build

..  uml:: buildIntegration.puml

Runtime call flow
*****************
.. Example request handled on ESP32, showing where control crosses the port boundary

..  uml:: runtimeCallFlow.puml

Folder layout
*************

.. code-block:: text

   Bico_Protocol_Bridge/
   ├── 3_swComp/                          # hardware independent
   │   ├── bicoSwComp.cmake               # exports BICO_SWCOMP_SOURCES / _INCLUDE_DIRS
   │   ├── layer1Driver/<drv>/
   │   │   ├── 3_inc/<drv>.h, <drv>Port.h # public API + port interface
   │   │   ├── 4_config/<drv>Cfg.h        # default configuration
   │   │   ├── 5_src/<drv>Unit.c          # generic driver, calls <drv>Port_*
   │   │   └── 6_test/gtest/fake/         # fake port for host tests
   │   ├── layer2Service/...
   │   └── layer3Application/...
   ├── 6_ut/                              # host build, BICO_BUILD_TESTS=ON
   ├── 7_1_esp32_workspace/<project>/     # hardware dependent (ESP32)
   │   ├── CMakeLists.txt                 # ESP-IDF project
   │   ├── main/main.cpp                  # setup()/loop() -> Init/Run
   │   └── main/
   │       ├── config/                    # optional cfg overrides
   │       ├── bico_protocol_bridge_swcomp/      # glue only: include(bicoSwComp.cmake)
   │       └── bico_protocol_bridge_port_esp32/  # xxxPortEsp32.c, ESP-IDF calls
   └── 7_2_stm32_workspace/               # future, same structure

