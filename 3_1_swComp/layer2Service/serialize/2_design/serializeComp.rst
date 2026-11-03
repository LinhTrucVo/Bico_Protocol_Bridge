#################################
What is this component about?
#################################

The Serialize service builds UDS (ISO 14229) response frames including positive responses
for ReadDataByIdentifier (0x62), WriteDataByIdentifier (0x6E), RoutineControl (0x71),
and negative responses (0x7F + NRC). It has no DID/RID semantic knowledge.


#################################
Static structure
#################################

..  uml:: serializeStaticStructure.puml

Public interfaces
#################################

..  sw-if:: serializeUnit.h
    :id: SWIF_SERIALIZE

    Public interface of serializeUnit.

    ..  sw-ifelement:: SerializeUnit_Init()
        :id: SWIFE_SERIALIZE_INIT
        :arguments:     return: Serialize_Status_t;

        Initializes the Serialize service and resets internal state.

        **Arguments:** None.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, BPB_SERIALIZE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serialize function.

    ..  sw-ifelement:: SerializeUnit_DeInit()
        :id: SWIFE_SERIALIZE_DEINIT
        :arguments:     return: Serialize_Status_t;

        De-initializes the Serialize service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildFrame()
        :id: SWIFE_SERIALIZE_BUILDFRAME
        :arguments:     return: Serialize_Status_t;    pMessage: const Serialize_Message_t*;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a complete serial frame from a generic message structure.

        **Arguments:**

        - **pMessage**: Pointer to the message descriptor containing header, payload pointer, and payload length.
        - **pOutBuffer**: Pointer to the output buffer descriptor (buffer pointer and buffer length).
        - **pFrameLength**: Pointer to receive the number of bytes written to the output buffer.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_TOO_SMALL if the output buffer is insufficient,
        BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** The output buffer must be at least SERIALIZE_CFG_MAX_FRAME_SIZE bytes.

    ..  sw-ifelement:: SerializeUnit_BuildError()
        :id: SWIFE_SERIALIZE_BUILDERROR
        :arguments:     return: Serialize_Status_t;    commandId: uint8_t;    sequenceId: uint8_t;    errorCode: Serialize_ErrorCode_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds an error response frame for the specified command and sequence.

        **Arguments:**

        - **commandId**: The command ID of the original request that caused the error.
        - **sequenceId**: The sequence ID of the original request.
        - **errorCode**: The error code to include in the response payload.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_TOO_SMALL if the output buffer is insufficient,
        BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildAnalogSamples()
        :id: SWIFE_SERIALIZE_BUILDANALOGSAMPLES
        :arguments:     return: Serialize_Status_t;    channelId: uint8_t;    pSamples: const uint16_t*;    sampleCount: uint16_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing ADC sample data for a given channel.

        **Arguments:**

        - **channelId**: The analog channel ID the samples belong to.
        - **pSamples**: Pointer to the array of 16-bit ADC samples.
        - **sampleCount**: Number of samples in the array.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, BPB_SERIALIZE_STATUS_BUFFER_OVERFLOW if sample data exceeds the frame size,
        BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero sample count.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildDigitalRead()
        :id: SWIFE_SERIALIZE_BUILDDIGITALREAD
        :arguments:     return: Serialize_Status_t;    pinId: uint8_t;    state: uint8_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing the digital read result for a given pin.

        **Arguments:**

        - **pinId**: The digital pin ID that was read.
        - **state**: The pin state (0 = LOW, 1 = HIGH).
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_TOO_SMALL if the output buffer is insufficient,
        BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildI2CRead()
        :id: SWIFE_SERIALIZE_BUILDI2CREAD
        :arguments:     return: Serialize_Status_t;    address: uint8_t;    pData: const uint8_t*;    length: uint16_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing I2C read data from the specified slave address.

        **Arguments:**

        - **address**: The I2C slave address the data was read from.
        - **pData**: Pointer to the received I2C data bytes.
        - **length**: Number of bytes in the I2C data buffer.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, BPB_SERIALIZE_STATUS_BUFFER_OVERFLOW if data exceeds the frame size,
        BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildSPITransfer()
        :id: SWIFE_SERIALIZE_BUILDSPITRANSFER
        :arguments:     return: Serialize_Status_t;    pTxData: const uint8_t*;    pRxData: const uint8_t*;    length: uint16_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing the received SPI data from a full-duplex transfer.

        **Arguments:**

        - **pTxData**: Pointer to the transmitted SPI data bytes (informational, may be NULL).
        - **pRxData**: Pointer to the received SPI data bytes.
        - **length**: Number of bytes transferred.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, BPB_SERIALIZE_STATUS_BUFFER_OVERFLOW if data exceeds the frame size,
        BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pRxData or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_ComputeCrc()
        :id: SWIFE_SERIALIZE_COMPUTECRC
        :arguments:     return: Serialize_Status_t;    pData: const uint8_t*;    length: uint16_t;    pCrc: uint16_t*;

        Computes the CRC-16 checksum over the provided data buffer.

        **Arguments:**

        - **pData**: Pointer to the data buffer.
        - **length**: Number of bytes to process.
        - **pCrc**: Pointer to receive the computed CRC-16 value.

        **Return values:** BPB_SERIALIZE_STATUS_OK on success, BPB_SERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: serializeStateMachine.puml

* Sequence diagram
..  uml:: serializeSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide UDS response frame construction for the Central Application Controller.

Assumptions and influencing factors:
************************************
* Response buffer is statically allocated (256 bytes max).
* DID/RID encoded big-endian in response frames.
* Caller provides response data; Serialize only assembles the frame.

Solutions list:
***************
Solution 1 - Builder pattern with dedicated functions
Separate build functions per response type (Read, Write, Routine, Negative).

Solution 2 - Generic frame builder
Single function with parameters for all frame types.

Solution evaluation:
********************
Builder pattern provides type safety and clear semantics per response type.

Final solution:
****************
Solution 1 selected for clarity and compile-time safety.