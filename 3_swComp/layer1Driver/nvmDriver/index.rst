nvmDriver Software Component
#############################

Introduction
************

The NVM Driver provides hardware abstraction for Non-Volatile Memory (flash) operations.
It handles memory initialization, read, write, and erase operations on the target platform.


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: nvmDriver
    :provides: nvmDriver.h – NVM initialization, read, write, and erase operations.
    :requires: Vendor HAL or register-level flash/NVM peripheral access.

Public interfaces
=================

..  sw-if:: nvmDriverUnit.h

    Public interface of nvmDriverUnit.

    ..  sw-ifelement:: NvmDriverUnit_Init()
        :arguments:     return: NvmDriver_Status_t;    pConfig: const NvmDriver_Config_t*;

        Initializes the NVM peripheral with the provided configuration structure.

        **Arguments:**

        - **pConfig**: Pointer to NVM driver configuration structure (base address, page size, sector size).

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** Must be called before any other NVM driver function.

    ..  sw-ifelement:: NvmDriverUnit_Read()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: uint8_t*;    length: uint32_t;

        Reads data from the specified NVM address into the provided buffer.

        **Arguments:**

        - **address**: Source NVM address to read from.
        - **pData**: Pointer to the destination buffer.
        - **length**: Number of bytes to read.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length, NVM_STATUS_ERROR for an out-of-range address.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_Write()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: const uint8_t*;    length: uint32_t;

        Writes data to the specified NVM address (requires prior erase).

        **Arguments:**

        - **address**: Destination NVM address to write to.
        - **pData**: Pointer to the source data buffer.
        - **length**: Number of bytes to write.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length, NVM_STATUS_ERROR if the target region is not erased or address is out of range.

        **Restrictions:** The target NVM region must be erased before writing.

    ..  sw-ifelement:: NvmDriverUnit_ErasePage()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;

        Erases the page containing the specified address.

        **Arguments:**

        - **address**: Any address within the page to erase.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_ERROR for an out-of-range address or erase failure.

        **Restrictions:** All data in the page is permanently destroyed.

    ..  sw-ifelement:: NvmDriverUnit_EraseSector()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;

        Erases the sector containing the specified address.

        **Arguments:**

        - **address**: Any address within the sector to erase.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_ERROR for an out-of-range address or erase failure.

        **Restrictions:** All data in the sector is permanently destroyed.

    ..  sw-ifelement:: NvmDriverUnit_EraseChip()
        :arguments:     return: NvmDriver_Status_t;

        Erases the entire NVM memory.

        **Arguments:** None.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_ERROR if the chip erase failed.

        **Restrictions:** All stored data is permanently destroyed. This operation may take significant time.

    ..  sw-ifelement:: NvmDriverUnit_WriteWithErase()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: const uint8_t*;    length: uint32_t;

        Erases the target region then writes data in a single operation.

        **Arguments:**

        - **address**: Destination NVM address to write to.
        - **pData**: Pointer to the source data buffer.
        - **length**: Number of bytes to write.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length, NVM_STATUS_ERROR on erase or write failure.

        **Restrictions:** This operation may take significant time due to the erase step.

    ..  sw-ifelement:: NvmDriverUnit_Verify()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    pData: const uint8_t*;    length: uint32_t;    pIsValid: bool*;

        Verifies that the NVM contents at the given address match the provided data.

        **Arguments:**

        - **address**: NVM address to verify.
        - **pData**: Pointer to the reference data buffer.
        - **length**: Number of bytes to compare.
        - **pIsValid**: Pointer to store the result; set to ``true`` if contents match.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_CalculateCrc()
        :arguments:     return: NvmDriver_Status_t;    address: NvmDriver_Address_t;    length: uint32_t;    pCrc: uint32_t*;

        Calculates a CRC checksum over the specified NVM region.

        **Arguments:**

        - **address**: Start NVM address for the CRC calculation.
        - **length**: Number of bytes to include in the CRC.
        - **pCrc**: Pointer to store the computed 32-bit CRC value.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_IsBusy()
        :arguments:     return: NvmDriver_Status_t;    pIsBusy: bool*;

        Returns whether an NVM operation is currently in progress.

        **Arguments:**

        - **pIsBusy**: Pointer to store the result; set to ``true`` if an operation is in progress.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_GetInfo()
        :arguments:     return: NvmDriver_Status_t;    pConfig: NvmDriver_Config_t*;

        Returns the NVM memory geometry and configuration.

        **Arguments:**

        - **pConfig**: Pointer to a configuration structure that receives the memory geometry (base address, page size, sector size, total size).

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_INVALID_PARAM for a NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_EnableWriteProtection()
        :arguments:     return: NvmDriver_Status_t;

        Activates hardware write protection.

        **Arguments:** None.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_ERROR if write protection could not be activated.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_DisableWriteProtection()
        :arguments:     return: NvmDriver_Status_t;

        Deactivates hardware write protection.

        **Arguments:** None.

        **Return values:** NVM_STATUS_OK on success, NVM_STATUS_ERROR if write protection could not be released.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmDriverUnit_RegisterCallback()
        :arguments:     return: NvmDriver_Status_t;    callback: NvmDriver_OperationCallback_t;

        Registers a callback invoked on operation completion.

        **Arguments:**

        - **callback**: Function pointer to the callback. Pass NULL to deregister.

        **Return values:** NVM_STATUS_OK on success.

        **Restrictions:** Callbacks are invoked from interrupt context; they must be short and non-blocking.

    ..  sw-ifelement:: NvmDriverUnit_DeInit()
        :arguments:     return: NvmDriver_Status_t;

        De-initializes the NVM peripheral and releases resources.

        **Arguments:** None.

        **Return values:** NVM_STATUS_OK on success.

        **Restrictions:** None.


Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/nvmDriverReq.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/nvmDriverComp.rst


Code documentation
******************

.. toctree::
    :maxdepth: 1

    ./2_design/nvmDriverCfg.rst
    ./2_design/nvmDriverUnit.rst
