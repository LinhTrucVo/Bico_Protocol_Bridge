#################################
What is this component about?
#################################

The NVM Driver abstracts non-volatile memory read, write, and erase operations.


#################################
Static structure
#################################

..  uml:: nvmDriverStaticStructure.puml

Public interfaces
#################################

..  sw-if:: nvmDriverUnit.h
    :id: SWIF_NVMDRIVER

    Public interface of nvmDriverUnit.

    ..  sw-ifelement:: NvmDriverUnit_Init()
        :id: SWIFE_NVMDRIVER_INIT
        :arguments:     return: NvmDriver_Status_t;    pConfig: const NvmDriver_Config_t*;

        Initializes the NVM peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to NVM driver configuration structure (base address, page size, sector size).

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other NVM driver function.

    ..  sw-ifelement:: NvmDriverUnit_Read()
        :id: SWIFE_NVMDRIVER_READ
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: uint8_t*;    length: uint32_t;

        Reads data from the specified NVM address into the provided buffer.

        **Arguments:**

        - **address**: Source NVM address to read from.
        - **pData**: Pointer to the destination buffer.
        - **length**: Number of bytes to read.

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_NVM_STATUS_ERROR for an out-of-range address.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_Write()
        :id: SWIFE_NVMDRIVER_WRITE
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: const uint8_t*;    length: uint32_t;

        Writes data to the specified NVM address (requires prior erase).

        **Arguments:**

        - **address**: Destination NVM address to write to.
        - **pData**: Pointer to the source data buffer.
        - **length**: Number of bytes to write.

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_NVM_STATUS_ERROR if the target region is not erased or address is out of range.

        **Restrictions:** The target NVM region must be erased before writing.

    ..  sw-ifelement:: NvmDriverUnit_ErasePage()
        :id: SWIFE_NVMDRIVER_ERASEPAGE
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;

        Erases the page containing the specified address.

        **Arguments:**

        - **address**: Any address within the page to erase.

        **Return values:** BPB_NVM_STATUS_OK on success, BPB_NVM_STATUS_ERROR for an out-of-range address or erase failure.

        **Restrictions:** All data in the page is permanently destroyed.

    ..  sw-ifelement:: NvmDriverUnit_EraseSector()
        :id: SWIFE_NVMDRIVER_ERASESECTOR
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;

        Erases the sector containing the specified address.

        **Arguments:**

        - **address**: Any address within the sector to erase.

        **Return values:** BPB_NVM_STATUS_OK on success, BPB_NVM_STATUS_ERROR for an out-of-range address or erase failure.

        **Restrictions:** All data in the sector is permanently destroyed.

    ..  sw-ifelement:: NvmDriverUnit_EraseChip()
        :id: SWIFE_NVMDRIVER_ERASECHIP
        :arguments:     return: NvmDriver_Status_t;

        Erases the entire NVM memory.

        **Arguments:** None.

        **Return values:** BPB_NVM_STATUS_OK on success, BPB_NVM_STATUS_ERROR if the chip erase failed.

        **Restrictions:** All stored data is permanently destroyed. This operation may take significant time.

    ..  sw-ifelement:: NvmDriverUnit_WriteWithErase()
        :id: SWIFE_NVMDRIVER_WRITEWITHERASE
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: const uint8_t*;    length: uint32_t;

        Erases the target region then writes data in a single operation.

        **Arguments:**

        - **address**: Destination NVM address to write to.
        - **pData**: Pointer to the source data buffer.
        - **length**: Number of bytes to write.

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length, BPB_NVM_STATUS_ERROR on erase or write failure.

        **Restrictions:** This operation may take significant time due to the erase step.

    ..  sw-ifelement:: NvmDriverUnit_Verify()
        :id: SWIFE_NVMDRIVER_VERIFY
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: const uint8_t*;    length: uint32_t;    pIsValid: bool*;

        Verifies that the NVM contents at the given address match the provided data.

        **Arguments:**

        - **address**: NVM address to verify.
        - **pData**: Pointer to the reference data buffer.
        - **length**: Number of bytes to compare.
        - **pIsValid**: Pointer to store the result; set to ``true`` if contents match.

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_CalculateCrc()
        :id: SWIFE_NVMDRIVER_CALCULATECRC
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    length: uint32_t;    pCrc: uint32_t*;

        Calculates a CRC checksum over the specified NVM region.

        **Arguments:**

        - **address**: Start NVM address for the CRC calculation.
        - **length**: Number of bytes to include in the CRC.
        - **pCrc**: Pointer to store the computed 32-bit CRC value.

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_IsBusy()
        :id: SWIFE_NVMDRIVER_ISBUSY
        :arguments:     return: NvmDriver_Status_t;    pIsBusy: bool*;

        Returns whether an NVM operation is currently in progress.

        **Arguments:**

        - **pIsBusy**: Pointer to store the result; set to ``true`` if an operation is in progress.

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_GetInfo()
        :id: SWIFE_NVMDRIVER_GETINFO
        :arguments:     return: NvmDriver_Status_t;    pConfig: NvmDriver_Config_t*;

        Returns the NVM memory geometry and configuration.

        **Arguments:**

        - **pConfig**: Pointer to a configuration structure that receives the memory geometry (base address, page size, sector size, total size).

        **Return values:** BPB_NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_EnableWriteProtection()
        :id: SWIFE_NVMDRIVER_ENABLEWRITEPROTECTION
        :arguments:     return: NvmDriver_Status_t;

        Activates hardware write protection.

        **Arguments:** None.

        **Return values:** BPB_NVM_STATUS_OK on success, BPB_NVM_STATUS_ERROR if write protection could not be activated.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_DisableWriteProtection()
        :id: SWIFE_NVMDRIVER_DISABLEWRITEPROTECTION
        :arguments:     return: NvmDriver_Status_t;

        Deactivates hardware write protection.

        **Arguments:** None.

        **Return values:** BPB_NVM_STATUS_OK on success, BPB_NVM_STATUS_ERROR if write protection could not be released.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_RegisterCallback()
        :id: SWIFE_NVMDRIVER_REGISTERCALLBACK
        :arguments:     return: NvmDriver_Status_t;    callback: NvmDriver_OperationCallback_t;

        Registers a callback invoked on operation completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** BPB_NVM_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: NvmDriverUnit_DeInit()
        :id: SWIFE_NVMDRIVER_DEINIT
        :arguments:     return: NvmDriver_Status_t;

        De-initializes the NVM peripheral and releases resources.

        **Arguments:** None.

        **Return values:** BPB_NVM_STATUS_OK on success.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml:: nvmDriverStateMachine.puml

* Sequence diagram
..  uml:: nvmDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable NVM abstraction with basic integrity support.

Assumptions and influencing factors:
************************************
* Vendor HAL provides flash/EEPROM operations.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor NVM HAL.

Solution 2 - External storage driver
Implement separate driver per memory type.

Solution evaluation:
********************
HAL wrapper keeps portability and simplifies integration.

Final solution:
****************
Solution 1 selected for portability.
