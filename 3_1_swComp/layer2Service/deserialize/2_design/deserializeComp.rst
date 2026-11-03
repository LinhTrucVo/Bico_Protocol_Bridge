#################################
What is this component about?
#################################

The Deserialize service parses UDS (ISO 14229) request frames extracting Service Identifier,
Data Identifier or Routine Identifier, and payload data. It has no DID/RID semantic knowledge.


#################################
Static structure
#################################

..  uml:: deserializeStaticStructure.puml

Public interfaces
#################################

..  sw-if:: deserializeUnit.h
    :id: SWIF_DESERIALIZE

    Public interface of deserializeUnit.

    ..  sw-ifelement:: DeserializeUnit_Init()
        :id: SWIFE_DESERIALIZE_INIT
        :arguments:     return: Deserialize_Status_t;

        Initializes the Deserialize service and resets internal state.

        **Arguments:** None.

        **Return values:** BPB_DESERIALIZE_STATUS_OK on success, BPB_DESERIALIZE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Deserialize function.

    ..  sw-ifelement:: DeserializeUnit_DeInit()
        :id: SWIFE_DESERIALIZE_DEINIT
        :arguments:     return: Deserialize_Status_t;

        De-initializes the Deserialize service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_DESERIALIZE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: DeserializeUnit_ValidateFrame()
        :id: SWIFE_DESERIALIZE_VALIDATEFRAME
        :arguments:     return: Deserialize_Status_t;    pFrame: const Deserialize_Frame_t*;

        Validates the structural integrity of an incoming frame (start byte, length, command range,
        optional CRC).

        **Arguments:**

        - **pFrame**: Pointer to the frame descriptor containing the raw byte buffer and its length.

        **Return values:** BPB_DESERIALIZE_STATUS_OK if valid, BPB_DESERIALIZE_STATUS_INVALID_FRAME for structural errors,
        DESERIALIZE_STATUS_CRC_ERROR for CRC mismatch, BPB_DESERIALIZE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: DeserializeUnit_ParseFrame()
        :id: SWIFE_DESERIALIZE_PARSEFRAME
        :arguments:     return: Deserialize_Status_t;    pFrame: const Deserialize_Frame_t*;    pRequest: Deserialize_Request_t*;

        Parses a validated frame into a structured request with command ID, sequence ID, command
        type, and payload pointer.

        **Arguments:**

        - **pFrame**: Pointer to the frame descriptor of the validated raw frame.
        - **pRequest**: Pointer to the request structure to populate.

        **Return values:** BPB_DESERIALIZE_STATUS_OK on success, DESERIALIZE_STATUS_UNSUPPORTED_CMD for unknown command,
        BPB_DESERIALIZE_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** Call ``DeserializeUnit_ValidateFrame()`` before calling this function.

    ..  sw-ifelement:: DeserializeUnit_ComputeCrc()
        :id: SWIFE_DESERIALIZE_COMPUTECRC
        :arguments:     return: Deserialize_Status_t;    pData: const uint8_t*;    length: uint16_t;    pCrc: uint16_t*;

        Computes the CRC-16 checksum over the provided data buffer.

        **Arguments:**

        - **pData**: Pointer to the data buffer.
        - **length**: Number of bytes to process.
        - **pCrc**: Pointer to the variable to receive the computed CRC value.

        **Return values:** BPB_DESERIALIZE_STATUS_OK on success, BPB_DESERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: deserializeStateMachine.puml

* Sequence diagram
..  uml:: deserializeSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide UDS frame structural parsing for request dispatching.

Assumptions and influencing factors:
************************************
* Frames arrive as complete byte buffers (no streaming).
* SID is always byte[0]; DID/RID are always big-endian 2-byte fields.
* Only SID 0x22, 0x2E, and 0x31 are supported.

Solutions list:
***************
Solution 1 - Switch-based SID parser
Parse based on SID value with per-SID length rules.

Solution 2 - Table-driven parser
Use a lookup table mapping SID to parsing function.

Solution evaluation:
********************
Switch-based is simpler with only 3 SIDs and minimal overhead.

Final solution:
****************
Solution 1 selected for clarity and minimal code complexity.