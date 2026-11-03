nvmDriver Software Component
#############################

Introduction
************

The NVM Driver provides hardware abstraction for Non-Volatile Memory (flash) operations.
It handles memory initialization, read, write, and erase operations on the target platform.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: nvmDriver
    :id: SWC_NVMDRIVER
    :provides: nvmDriver.h – NVM initialization, read, write, and erase operations.
    :requires: Vendor HAL or register-level flash/NVM peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/nvmDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/nvmDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/nvmDriverCfg.rst
    ./2_design/nvmDriverUnit.rst
