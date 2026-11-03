configService Software Component
##################################

Introduction
************

The Config Service provides a centralized interface for storing and retrieving configuration
parameters for all protocol bridge channels: serial port, analog inputs, digital pins, PWM outputs,
I2C, and SPI. It validates parameters before applying them and serves as the single source of truth
for runtime configuration.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: configService
    :id: SWC_CONFIGSERVICE
    :provides: configService.h – get/set and validate configuration for serial, analog, digital, PWM, I2C, and SPI channels.
    :requires: No lower-layer driver dependency; persistence is delegated to nvmService.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/configServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/configServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/configServiceCfg.rst
    ./2_design/configServiceUnit.rst
