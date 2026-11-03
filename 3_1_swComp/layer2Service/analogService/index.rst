AnalogService Software Component
######################################

Introduction
************

The Analog Service handles all ADC-related commands received from the host via the
serial interface. It configures ADC channels, triggers sampling, optionally applies averaging and
filtering, and returns the digitized results as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: AnalogService
    :id: SWC_ANALOGSERVICE
    :provides: AnalogService.h – ADC channel configuration, sampling, and response building for Analog Service bridging.
    :requires: adcDriver.h, serialize.h, configService.h.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/AnalogServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/AnalogServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/AnalogServiceCfg.rst
    ./2_design/AnalogServiceUnit.rst
