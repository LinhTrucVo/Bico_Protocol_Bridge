nvmService Software Component
##############################

Introduction
************

The NVM Service provides key-based persistent storage on top of the NVM Driver. It abstracts
raw flash operations into a simple blob store with key lookup, optional compression, and CRC
integrity verification. It is used to save and restore configuration and application state across
power cycles.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: nvmService
    :id: SWC_NVMSERVICE
    :provides: nvmService.h – key-based persistent blob save, load, erase, and CRC verification.
    :requires: nvmDriver.h – low-level NVM read, write, erase, and verify operations.

Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/nvmServiceReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/nvmServiceComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/nvmServiceCfg.rst
    ./2_design/nvmServiceUnit.rst
