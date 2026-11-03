deserialize Software Component
################################

Introduction
************

The Deserialize service parses incoming serial frames received from the host into structured command
requests. It validates frame integrity, optionally verifies the CRC, and extracts the command ID,
sequence ID, and payload for routing to the appropriate application handler.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: deserialize
    :id: SWC_DESERIALIZE
    :provides: deserialize.h – frame validation, parsing, and CRC computation for incoming serial frames.
    :requires: serialDriver.h – raw received byte stream.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/deserializeReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/deserializeComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/deserializeCfg.rst
    ./2_design/deserializeUnit.rst
