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
    :provides: deserialize.h – frame validation, parsing, and CRC computation for incoming serial frames.
    :requires: serialDriver.h – raw received byte stream.

Public interfaces
=================

..  sw-if:: deserializeUnit.h

    Public interface of deserializeUnit.

    ..  sw-ifelement:: DeserializeUnit_Init()
        :arguments:     return: Deserialize_Status_t;

        Initializes the Deserialize service and resets internal state.

        **Arguments:** None.

        **Return values:** DESERIALIZE_STATUS_OK on success, DESERIALIZE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Deserialize function.

    ..  sw-ifelement:: DeserializeUnit_DeInit()
        :arguments:     return: Deserialize_Status_t;

        De-initializes the Deserialize service and releases resources.

        **Arguments:** None.

        **Return values:** DESERIALIZE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: DeserializeUnit_ValidateFrame()
        :arguments:     return: Deserialize_Status_t;    pFrame: const Deserialize_Frame_t*;

        Validates the structural integrity of an incoming frame (start byte, length, command range,
        optional CRC).

        **Arguments:**

        - **pFrame**: Pointer to the frame descriptor containing the raw byte buffer and its length.

        **Return values:** DESERIALIZE_STATUS_OK if valid, DESERIALIZE_STATUS_INVALID_FRAME for structural errors,
        DESERIALIZE_STATUS_CRC_ERROR for CRC mismatch, DESERIALIZE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: DeserializeUnit_ParseFrame()
        :arguments:     return: Deserialize_Status_t;    pFrame: const Deserialize_Frame_t*;    pRequest: Deserialize_Request_t*;

        Parses a validated frame into a structured request with command ID, sequence ID, command
        type, and payload pointer.

        **Arguments:**

        - **pFrame**: Pointer to the frame descriptor of the validated raw frame.
        - **pRequest**: Pointer to the request structure to populate.

        **Return values:** DESERIALIZE_STATUS_OK on success, DESERIALIZE_STATUS_UNSUPPORTED_CMD for unknown command,
        DESERIALIZE_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** Call ``DeserializeUnit_ValidateFrame()`` before calling this function.

    ..  sw-ifelement:: DeserializeUnit_ComputeCrc()
        :arguments:     return: Deserialize_Status_t;    pData: const uint8_t*;    length: uint16_t;    pCrc: uint16_t*;

        Computes the CRC-16 checksum over the provided data buffer.

        **Arguments:**

        - **pData**: Pointer to the data buffer.
        - **length**: Number of bytes to process.
        - **pCrc**: Pointer to the variable to receive the computed CRC value.

        **Return values:** DESERIALIZE_STATUS_OK on success, DESERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.


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
