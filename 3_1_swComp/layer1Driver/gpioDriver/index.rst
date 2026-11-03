gpioDriver Software Component
##############################

Introduction
************

The GPIO Driver provides hardware abstraction for General Purpose Input/Output pin management.
It handles GPIO initialization, pin direction configuration, and pin read/write operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: gpioDriver
    :id: SWC_GPIODRIVER
    :provides: gpioDriver.h – GPIO initialization, pin direction configuration, and pin read/write operations.
    :requires: Vendor HAL or register-level GPIO peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/gpioDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/gpioDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/gpioDriverCfg.rst
    ./2_design/gpioDriverUnit.rst
