#################################
What is this component about?
#################################

The SPI Master Driver abstracts SPI master configuration and transfers.


#################################
Static structure
#################################

..  uml:: spiMasterDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: spiMasterDriverUnit.h
    :id: SWIF_SPIMASTERDRIVER

    Public interface of spiMasterDriverUnit.

    ..  sw-ifelement:: SpiMasterDriverUnit_Init()
        :id: SWIFE_SPIMASTERDRIVER_INIT
        :arguments:     return: SpiMasterDriver_Status_t;    pConfig: const SpiMasterDriver_Config_t*;

        Initializes the SPI master peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to SPI master driver configuration structure (clockSpeed, mode, bitOrder).

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other SPI master driver function.

    ..  sw-ifelement:: SpiMasterDriverUnit_Configure()
        :id: SWIFE_SPIMASTERDRIVER_CONFIGURE
        :arguments:     return: SpiMasterDriver_Status_t;    clockSpeed: uint32_t;    mode: SpiMasterDriver_Mode_t;    bitOrder: SpiMasterDriver_BitOrder_t;

        Reconfigures clock speed, SPI mode, and bit order at runtime.

        **Arguments:**

        - **clockSpeed**: Desired SPI clock speed in Hz.
        - **mode**: SPI mode (BPB_SPI_MODE_0, BPB_SPI_MODE_1, BPB_SPI_MODE_2, BPB_SPI_MODE_3).
        - **bitOrder**: Bit transmission order (SPI_BIT_ORDER_MSB_FIRST or SPI_BIT_ORDER_LSB_FIRST).

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for unsupported values.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_SelectChip()
        :id: SWIFE_SPIMASTERDRIVER_SELECTCHIP
        :arguments:     return: SpiMasterDriver_Status_t;    cs: SpiMasterDriver_ChipSelect_t;

        Asserts (activates) the specified chip-select line.

        **Arguments:**

        - **cs**: Chip-select identifier to assert.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for an invalid chip-select.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_DeselectChip()
        :id: SWIFE_SPIMASTERDRIVER_DESELECTCHIP
        :arguments:     return: SpiMasterDriver_Status_t;    cs: SpiMasterDriver_ChipSelect_t;

        Deasserts (releases) the specified chip-select line.

        **Arguments:**

        - **cs**: Chip-select identifier to release.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for an invalid chip-select.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_Transmit()
        :id: SWIFE_SPIMASTERDRIVER_TRANSMIT
        :arguments:     return: SpiMasterDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;

        Transmits data over SPI (receive data is discarded).

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_SPI_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_Receive()
        :id: SWIFE_SPIMASTERDRIVER_RECEIVE
        :arguments:     return: SpiMasterDriver_Status_t;    pData: uint8_t*;    length: uint16_t;

        Receives data over SPI (dummy bytes are transmitted).

        **Arguments:**

        - **pData**: Pointer to the buffer for received data.
        - **length**: Number of bytes to receive.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_SPI_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_TransmitReceive()
        :id: SWIFE_SPIMASTERDRIVER_TRANSMITRECEIVE
        :arguments:     return: SpiMasterDriver_Status_t;    pTxData: const uint8_t*;    pRxData: uint8_t*;    length: uint16_t;

        Performs a full-duplex SPI transfer.

        **Arguments:**

        - **pTxData**: Pointer to the data buffer to transmit.
        - **pRxData**: Pointer to the buffer for received data.
        - **length**: Number of bytes to transfer.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for NULL pointers or zero length, BPB_SPI_MASTER_STATUS_TIMEOUT on timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_TransmitWithTimeout()
        :id: SWIFE_SPIMASTERDRIVER_TRANSMITWITHTIMEOUT
        :arguments:     return: SpiMasterDriver_Status_t;    pData: const uint8_t*;    length: uint16_t;    timeoutMs: uint32_t;

        Transmits data with an explicit timeout.

        **Arguments:**

        - **pData**: Pointer to the data buffer to transmit.
        - **length**: Number of bytes to transmit.
        - **timeoutMs**: Maximum time in milliseconds to wait for completion.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_SPI_MASTER_STATUS_TIMEOUT if the operation exceeded the timeout.

        **Restrictions:** Chip-select must be asserted before calling this function.

    ..  sw-ifelement:: SpiMasterDriverUnit_IsBusy()
        :id: SWIFE_SPIMASTERDRIVER_ISBUSY
        :arguments:     return: SpiMasterDriver_Status_t;    pIsBusy: bool*;

        Returns whether the SPI bus is currently busy.

        **Arguments:**

        - **pIsBusy**: Pointer to store the result; set to ``true`` if the bus is busy.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success, BPB_SPI_MASTER_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: SpiMasterDriverUnit_RegisterCallback()
        :id: SWIFE_SPIMASTERDRIVER_REGISTERCALLBACK
        :arguments:     return: SpiMasterDriver_Status_t;    callback: SpiMasterDriver_Callback_t;

        Registers a callback invoked on transfer completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: SpiMasterDriverUnit_DeInit()
        :id: SWIFE_SPIMASTERDRIVER_DEINIT
        :arguments:     return: SpiMasterDriver_Status_t;

        De-initializes the SPI master peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_SPI_MASTER_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: spiMasterDriverStateMachine.puml

* Sequence diagram
..  uml:: spiMasterDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable SPI master abstraction with chip select handling.

Assumptions and influencing factors:
************************************
* Vendor HAL provides SPI transfer operations.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor SPI HAL.

Solution 2 - Bit-banging
Software-driven SPI for maximum portability.

Solution evaluation:
********************
HAL wrapper ensures timing accuracy and performance.

Final solution:
****************
Solution 1 selected for performance and portability.
