centralAppController Software Component
########################################

Introduction
************

The Central Application Controller is the top-level dispatcher of the protocol bridge. It receives
raw serial frames from the serial driver, delegates deserialization, routes commands to the
appropriate application handler (analog, digital, I2C, SPI), and serializes the response back to
the host. It manages the overall processing state machine and error reporting.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: centralAppController
    :id: SWC_CENTRALAPPCONTROLLER
    :provides: centralAppController.h – top-level application dispatch, frame routing, and state management.
    :requires: deserialize.h, serialize.h, ANALOGAPP.h, DIGITALAPP.h, I2CAPP.h, SPIAPP.h.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/centralAppControllerReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/centralAppControllerComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/centralAppControllerCfg.rst
    ./2_design/centralAppControllerUnit.rst
