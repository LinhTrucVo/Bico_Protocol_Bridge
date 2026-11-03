i2cMasterDriver Software Component
####################################

Introduction
************

The I2C Master Driver provides hardware abstraction for the I2C communication protocol in master mode.
It handles bus initialization, device addressing, and data read/write transfer operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: i2cMasterDriver
    :id: SWC_I2CMASTERDRIVER
    :provides: i2cMasterDriver.h – I2C master bus initialization, device addressing, and data transfer operations.
    :requires: Vendor HAL or register-level I2C peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/i2cMasterDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/i2cMasterDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/i2cMasterDriverCfg.rst
    ./2_design/i2cMasterDriverUnit.rst
