SpiService Software Component
###################################

Introduction
************

The SPI Service handles SPI master transfer commands received from the host via the
serial interface. It configures the SPI master driver, executes full-duplex transfers to slave
devices, and returns the received data as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: SpiService
    :id: SWC_SPISERVICE
    :provides: SpiService.h – SPI master full-duplex transfer execution for SPI Service bridging.
    :requires: spiMasterDriver.h, serialize.h, configService.h.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/SpiServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/SpiServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/SpiServiceCfg.rst
    ./2_design/SpiServiceUnit.rst
