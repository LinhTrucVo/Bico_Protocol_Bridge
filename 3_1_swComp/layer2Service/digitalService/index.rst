DigitalService Software Component
#######################################

Introduction
************

The Digital Service handles GPIO and PWM commands received from the host via the
serial interface. It configures digital pins and PWM channels, executes read/write/toggle
operations, and returns the result as a serialized response frame.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: DigitalService
    :id: SWC_DIGITALSERVICE
    :provides: DigitalService.h – GPIO pin and PWM channel control for Digital Service bridging.
    :requires: gpioDriver.h, pwmDriver.h, serialize.h, configService.h.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/DigitalServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/DigitalServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/DigitalServiceCfg.rst
    ./2_design/DigitalServiceUnit.rst
