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
    :provides: nvmService.h – key-based persistent blob save, load, erase, and CRC verification.
    :requires: nvmDriver.h – low-level NVM read, write, erase, and verify operations.

Public interfaces
=================

..  sw-if:: nvmServiceUnit.h

    Public interface of nvmServiceUnit.

    ..  sw-ifelement:: NvmServiceUnit_Init()
        :arguments:     return: NvmService_Status_t;

        Initializes the NVM Service and the underlying NVM driver.

        **Arguments:** None.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other NVM Service function.

    ..  sw-ifelement:: NvmServiceUnit_DeInit()
        :arguments:     return: NvmService_Status_t;

        De-initializes the NVM Service and releases resources.

        **Arguments:** None.

        **Return values:** NVM_SERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_Save()
        :arguments:     return: NvmService_Status_t;    pBlob: const NvmService_Blob_t*;

        Saves a data blob identified by a key to NVM, erasing the previous entry if it exists.

        **Arguments:**

        - **pBlob**: Pointer to the blob descriptor containing the key, data pointer, and data length.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_FULL if no space remains,
        NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointer or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_Load()
        :arguments:     return: NvmService_Status_t;    key: NvmService_Key_t;    pData: uint8_t*;    maxLength: uint16_t;    pOutLength: uint16_t*;

        Loads a previously saved blob identified by key from NVM into the provided buffer.

        **Arguments:**

        - **key**: The key identifying the stored blob (e.g. NVM_SERVICE_KEY_SYSTEM_CONFIG).
        - **pData**: Pointer to the output buffer to receive the loaded data.
        - **maxLength**: Maximum number of bytes the output buffer can hold.
        - **pOutLength**: Pointer to receive the actual number of bytes loaded.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_NOT_FOUND if key does not exist,
        NVM_SERVICE_STATUS_CRC_ERROR if stored data is corrupt, NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_Erase()
        :arguments:     return: NvmService_Status_t;    key: NvmService_Key_t;

        Erases the stored blob identified by key.

        **Arguments:**

        - **key**: The key identifying the blob to erase.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_NOT_FOUND if key does not exist.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_EraseAll()
        :arguments:     return: NvmService_Status_t;

        Erases all stored blobs and resets the NVM storage area.

        **Arguments:** None.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_ERROR on failure.

        **Restrictions:** All stored data will be permanently lost.

    ..  sw-ifelement:: NvmServiceUnit_Exists()
        :arguments:     return: NvmService_Status_t;    key: NvmService_Key_t;    pExists: bool*;

        Checks whether a blob with the given key exists in NVM.

        **Arguments:**

        - **key**: The key to search for.
        - **pExists**: Pointer to receive true if the key exists, false otherwise.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_ComputeCrc()
        :arguments:     return: NvmService_Status_t;    pData: const uint8_t*;    length: uint16_t;    pCrc: uint32_t*;

        Computes a CRC-32 checksum over the provided data buffer.

        **Arguments:**

        - **pData**: Pointer to the data buffer.
        - **length**: Number of bytes to process.
        - **pCrc**: Pointer to receive the computed CRC-32 value.

        **Return values:** NVM_SERVICE_STATUS_OK on success, NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.


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
