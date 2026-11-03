adcDriver Software Component
#############################

Introduction
************

The ADC Driver provides hardware abstraction for Analog-to-Digital Converter peripherals.
It handles ADC initialization, channel configuration, start/stop conversion, and value reading.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: adcDriver
    :id: SWC_ADCDRIVER
    :provides: adcDriver.h – ADC initialization, channel configuration, start/stop conversion, and value reading.
    :requires: Vendor HAL or register-level ADC peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/adcDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/adcDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/adcDriverCfg.rst
    ./2_design/adcDriverUnit.rst
