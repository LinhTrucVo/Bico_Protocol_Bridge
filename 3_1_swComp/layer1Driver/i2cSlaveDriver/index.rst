i2cSlaveDriver Software Component
###################################

Introduction
************

The I2C Slave Driver provides hardware abstraction for the I2C communication protocol in slave mode.
It handles slave address configuration and data reception/transmission under master control.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: i2cSlaveDriver
    :id: SWC_I2CSLAVEDRIVER
    :provides: i2cSlaveDriver.h – I2C slave initialization, address configuration, and data transfer operations.
    :requires: Vendor HAL or register-level I2C peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/i2cSlaveDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/i2cSlaveDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/i2cSlaveDriverCfg.rst
    ./2_design/i2cSlaveDriverUnit.rst
