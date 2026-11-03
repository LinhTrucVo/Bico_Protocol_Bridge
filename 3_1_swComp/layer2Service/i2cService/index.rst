I2cService Software Component
###################################

Introduction
************

The I2C Service handles I2C master transaction commands received from the host via
the serial interface. It configures the I2C master driver, executes write, read, and combined
write-read transactions to slave devices, and returns the result as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: I2cService
    :id: SWC_I2CSERVICE
    :provides: I2cService.h – I2C master transaction execution for I2C Service bridging.
    :requires: i2cMasterDriver.h, serialize.h, configService.h.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/I2cServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/I2cServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/I2cServiceCfg.rst
    ./2_design/I2cServiceUnit.rst
