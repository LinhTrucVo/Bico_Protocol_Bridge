pwmDriver Software Component
#############################

Introduction
************

The PWM Driver provides hardware abstraction for Pulse Width Modulation signal generation.
It handles timer initialization, duty cycle configuration, frequency control, and channel enable/disable.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: pwmDriver
    :id: SWC_PWMDRIVER
    :provides: pwmDriver.h – PWM initialization, duty cycle configuration, frequency control, and channel management.
    :requires: Vendor HAL or register-level timer/PWM peripheral access.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/pwmDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/pwmDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/pwmDriverCfg.rst
    ./2_design/pwmDriverUnit.rst
