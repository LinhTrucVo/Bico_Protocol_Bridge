spiSlaveDriver Software Component
###################################

Introduction
************

The SPI Slave Driver provides hardware abstraction for the SPI communication protocol in slave mode.
It handles slave configuration and data reception/transmission under master control.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: spiSlaveDriver
    :id: SWC_SPISLAVEDRIVER
    :provides: spiSlaveDriver.h – SPI slave initialization, mode configuration, and data transfer operations.
    :requires: Vendor HAL or register-level SPI peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/spiSlaveDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/spiSlaveDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/spiSlaveDriverCfg.rst
    ./2_design/spiSlaveDriverUnit.rst
