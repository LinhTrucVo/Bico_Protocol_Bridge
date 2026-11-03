serialDriver Software Component
################################

Introduction
************

The Serial Driver provides hardware abstraction for UART/USART serial communication.
It handles serial port initialization, baud rate configuration, and data transmission/reception operations.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: serialDriver
    :id: SWC_SERIALDRIVER
    :provides: serialDriver.h – Serial port initialization, baud rate configuration, and data transmit/receive operations.
    :requires: Vendor HAL or register-level UART/USART peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/serialDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/serialDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/serialDriverCfg.rst
    ./2_design/serialDriverUnit.rst
