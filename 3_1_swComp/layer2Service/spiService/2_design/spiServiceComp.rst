#################################
What is this component about?
#################################

The Serial-to-SPI Application provides typed SPI write and transceive operations. It is
called by the Central Application Controller via RID 0x0500 (SPI Write) and
RID 0x0501 (SPI Transceive). Receives typed parameters and returns typed results.


#################################
Static structure
#################################

..  uml:: SpiServiceStaticStructure.puml

Public interfaces
#################################

..  sw-if:: SpiServiceUnit.h
    :id: SWIF_SPISERVICE

    Public interface of SpiServiceUnit.

    ..  sw-ifelement:: SpiServiceUnit_Init()
        :id: SWIFE_SPISERVICE_INIT
        :arguments:     return: SpiService_Status_t;

        Initializes the SPI Service and configures the SPI master driver with
        default settings.

        **Arguments:** None.

        **Return values:** BPB_SPISERVICE_STATUS_OK on success, BPB_SPISERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other SPI Service function.

    ..  sw-ifelement:: SpiServiceUnit_DeInit()
        :id: SWIFE_SPISERVICE_DEINIT
        :arguments:     return: SpiService_Status_t;

        De-initializes the SPI Service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_SPISERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiServiceUnit_Run()
        :id: SWIFE_SPISERVICE_RUN
        :arguments:     return: SpiService_Status_t;

        Executes one cycle of the SPI processing loop (handles asynchronous transfer completion).

        **Arguments:** None.

        **Return values:** BPB_SPISERVICE_STATUS_OK on success, BPB_SPISERVICE_STATUS_NOT_INITIALIZED if called before Init.

        **Restrictions:** Must be called periodically from the main loop when asynchronous SPI transfers are in use.

    ..  sw-ifelement:: SpiServiceUnit_ProcessFrame()
        :id: SWIFE_SPISERVICE_PROCESSFRAME
        :arguments:     return: SpiService_Status_t;    pFrame: const uint8_t*;    frameLength: uint16_t;    pResponse: uint8_t*;    pResponseLength: uint16_t*;

        Processes an incoming SPI transfer command frame and fills the output buffer with the
        serialized response containing the received SPI data.

        **Arguments:**

        - **pFrame**: Pointer to the raw incoming frame bytes.
        - **frameLength**: Length of the incoming frame in bytes.
        - **pResponse**: Pointer to the output buffer for the serialized response.
        - **pResponseLength**: Pointer to receive the number of bytes written to the response buffer.

        **Return values:** BPB_SPISERVICE_STATUS_OK on success, BPB_SPISERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length,
        BPB_SPISERVICE_STATUS_ERROR on SPI transfer or serialization failure.

        **Restrictions:** The response buffer must be large enough to hold the maximum response frame.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: SpiServiceStateMachine.puml

* Sequence diagram
..  uml:: SpiServiceSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide hardware-abstracted SPI write and full-duplex transceive for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* SPI master driver is initialized and available.
* Device selection is handled via device index (chip select managed by driver).

Solutions list:
***************
Solution 1 - Write + Transceive functions
Expose Write(dev, pData, len) and Transceive(dev, pTx, txLen, pRx, rxLen).

Solution 2 - Single transfer function with mode parameter
Combined function handling both write-only and full-duplex.

Solution evaluation:
********************
Separate functions match the RID mapping and provide clearer API semantics.

Final solution:
****************
Solution 1 selected for clarity and RID alignment.