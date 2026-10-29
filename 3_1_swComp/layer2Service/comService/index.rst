comService Software Component
################################

Introduction
************

The ComService provides a buffered communication abstraction over the Serial Driver.
It manages Rx and Tx ring-buffers, providing upper layers with simple APIs to check
data availability, read received frames, and write outgoing frames without direct
dependency on the Serial Driver.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: comService
    :provides: comService.h – buffered communication API (init, run, read, write, data availability).
    :requires: serialDriver.h – raw serial byte transfer.

Public interfaces
=================
