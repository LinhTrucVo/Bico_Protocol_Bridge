spiMasterDriver Software Component
####################################

Introduction
************

The SPI Master Driver provides hardware abstraction for the SPI communication protocol in master mode.
It handles bus initialization, clock configuration, chip select management, and data transfer operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: spiMasterDriver
    :id: SWC_SPIMASTERDRIVER
    :provides: spiMasterDriver.h – SPI master bus initialization, clock configuration, chip select management, and data transfer.
    :requires: Vendor HAL or register-level SPI peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/spiMasterDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/spiMasterDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/spiMasterDriverCfg.rst
    ./2_design/spiMasterDriverUnit.rst
