serialize Software Component
##############################

Introduction
************

The Serialize service builds outgoing serial frames from structured response data. It formats
response messages with header, payload, and CRC fields for transmission back to the host. It
provides dedicated builders for analog samples, digital reads, I2C reads, SPI transfers, and
generic error responses.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: serialize
    :provides: serialize.h – frame building and CRC generation for serial responses to the host.
    :requires: serialDriver.h – raw serial byte transmission.

Public interfaces
=================

..  sw-if:: serializeUnit.h

    Public interface of serializeUnit.

    ..  sw-ifelement:: SerializeUnit_Init()
        :arguments:     return: Serialize_Status_t;

        Initializes the Serialize service and resets internal state.

        **Arguments:** None.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other Serialize function.

    ..  sw-ifelement:: SerializeUnit_DeInit()
        :arguments:     return: Serialize_Status_t;

        De-initializes the Serialize service and releases resources.

        **Arguments:** None.

        **Return values:** SERIALIZE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildFrame()
        :arguments:     return: Serialize_Status_t;    pMessage: const Serialize_Message_t*;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a complete serial frame from a generic message structure.

        **Arguments:**

        - **pMessage**: Pointer to the message descriptor containing header, payload pointer, and payload length.
        - **pOutBuffer**: Pointer to the output buffer descriptor (buffer pointer and buffer length).
        - **pFrameLength**: Pointer to receive the number of bytes written to the output buffer.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_TOO_SMALL if the output buffer is insufficient,
        SERIALIZE_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** The output buffer must be at least SERIALIZE_CFG_MAX_FRAME_SIZE bytes.

    ..  sw-ifelement:: SerializeUnit_BuildError()
        :arguments:     return: Serialize_Status_t;    commandId: uint8_t;    sequenceId: uint8_t;    errorCode: Serialize_ErrorCode_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds an error response frame for the specified command and sequence.

        **Arguments:**

        - **commandId**: The command ID of the original request that caused the error.
        - **sequenceId**: The sequence ID of the original request.
        - **errorCode**: The error code to include in the response payload.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_TOO_SMALL if the output buffer is insufficient,
        SERIALIZE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildAnalogSamples()
        :arguments:     return: Serialize_Status_t;    channelId: uint8_t;    pSamples: const uint16_t*;    sampleCount: uint16_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing ADC sample data for a given channel.

        **Arguments:**

        - **channelId**: The analog channel ID the samples belong to.
        - **pSamples**: Pointer to the array of 16-bit ADC samples.
        - **sampleCount**: Number of samples in the array.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_OVERFLOW if sample data exceeds the frame size,
        SERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero sample count.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildDigitalRead()
        :arguments:     return: Serialize_Status_t;    pinId: uint8_t;    state: uint8_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing the digital read result for a given pin.

        **Arguments:**

        - **pinId**: The digital pin ID that was read.
        - **state**: The pin state (0 = LOW, 1 = HIGH).
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_TOO_SMALL if the output buffer is insufficient,
        SERIALIZE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildI2CRead()
        :arguments:     return: Serialize_Status_t;    address: uint8_t;    pData: const uint8_t*;    length: uint16_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing I2C read data from the specified slave address.

        **Arguments:**

        - **address**: The I2C slave address the data was read from.
        - **pData**: Pointer to the received I2C data bytes.
        - **length**: Number of bytes in the I2C data buffer.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_OVERFLOW if data exceeds the frame size,
        SERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_BuildSPITransfer()
        :arguments:     return: Serialize_Status_t;    pTxData: const uint8_t*;    pRxData: const uint8_t*;    length: uint16_t;    pOutBuffer: Serialize_Buffer_t*;    pFrameLength: uint16_t*;

        Builds a response frame containing the received SPI data from a full-duplex transfer.

        **Arguments:**

        - **pTxData**: Pointer to the transmitted SPI data bytes (informational, may be NULL).
        - **pRxData**: Pointer to the received SPI data bytes.
        - **length**: Number of bytes transferred.
        - **pOutBuffer**: Pointer to the output buffer descriptor.
        - **pFrameLength**: Pointer to receive the number of bytes written.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_BUFFER_OVERFLOW if data exceeds the frame size,
        SERIALIZE_STATUS_INVALID_PARAM for NULL pRxData or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: SerializeUnit_ComputeCrc()
        :arguments:     return: Serialize_Status_t;    pData: const uint8_t*;    length: uint16_t;    pCrc: uint16_t*;

        Computes the CRC-16 checksum over the provided data buffer.

        **Arguments:**

        - **pData**: Pointer to the data buffer.
        - **length**: Number of bytes to process.
        - **pCrc**: Pointer to receive the computed CRC-16 value.

        **Return values:** SERIALIZE_STATUS_OK on success, SERIALIZE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/serializeReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/serializeComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/serializeCfg.rst
    ./2_design/serializeUnit.rst
