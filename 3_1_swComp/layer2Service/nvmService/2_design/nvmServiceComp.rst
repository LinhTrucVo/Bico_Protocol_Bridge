#################################
What is this component about?
#################################

The NVM Service provides key-based storage for configuration data.
It wraps the NVM driver with CRC-protected storage for higher-level modules.


#################################
Static structure
#################################

Files:
* nvmService.h
* nvmServiceCfg.h
* nvmServiceUnit.c

..  uml::

	@startuml
	class NvmService_Blob
	class NvmIndex
	@enduml

Public interfaces
#################################

..  sw-if:: nvmServiceUnit.h
    :id: SWIF_NVMSERVICE

    Public interface of nvmServiceUnit.

    ..  sw-ifelement:: NvmServiceUnit_Init()
        :id: SWIFE_NVMSERVICE_INIT
        :arguments:     return: NvmService_Status_t;

        Initializes the NVM Service and the underlying NVM driver.

        **Arguments:** None.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_ERROR on failure.

        **Restrictions:** Must be called before any other NVM Service function.

    ..  sw-ifelement:: NvmServiceUnit_DeInit()
        :id: SWIFE_NVMSERVICE_DEINIT
        :arguments:     return: NvmService_Status_t;

        De-initializes the NVM Service and releases resources.

        **Arguments:** None.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_Save()
        :id: SWIFE_NVMSERVICE_SAVE
        :arguments:     return: NvmService_Status_t;    pBlob: const NvmService_Blob_t*;

        Saves a data blob identified by a key to NVM, erasing the previous entry if it exists.

        **Arguments:**

        - **pBlob**: Pointer to the blob descriptor containing the key, data pointer, and data length.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_FULL if no space remains,
        BPB_NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointer or zero length.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_Load()
        :id: SWIFE_NVMSERVICE_LOAD
        :arguments:     return: NvmService_Status_t;    key: NvmService_Key_t;    pData: uint8_t*;    maxLength: uint16_t;    pOutLength: uint16_t*;

        Loads a previously saved blob identified by key from NVM into the provided buffer.

        **Arguments:**

        - **key**: The key identifying the stored blob (e.g. BPB_NVM_SERVICE_KEY_SYSTEM_CONFIG).
        - **pData**: Pointer to the output buffer to receive the loaded data.
        - **maxLength**: Maximum number of bytes the output buffer can hold.
        - **pOutLength**: Pointer to receive the actual number of bytes loaded.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_NOT_FOUND if key does not exist,
        BPB_NVM_SERVICE_STATUS_CRC_ERROR if stored data is corrupt, BPB_NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointers.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_Erase()
        :id: SWIFE_NVMSERVICE_ERASE
        :arguments:     return: NvmService_Status_t;    key: NvmService_Key_t;

        Erases the stored blob identified by key.

        **Arguments:**

        - **key**: The key identifying the blob to erase.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_NOT_FOUND if key does not exist.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_EraseAll()
        :id: SWIFE_NVMSERVICE_ERASEALL
        :arguments:     return: NvmService_Status_t;

        Erases all stored blobs and resets the NVM storage area.

        **Arguments:** None.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_ERROR on failure.

        **Restrictions:** All stored data will be permanently lost.

    ..  sw-ifelement:: NvmServiceUnit_Exists()
        :id: SWIFE_NVMSERVICE_EXISTS
        :arguments:     return: NvmService_Status_t;    key: NvmService_Key_t;    pExists: bool*;

        Checks whether a blob with the given key exists in NVM.

        **Arguments:**

        - **key**: The key to search for.
        - **pExists**: Pointer to receive true if the key exists, false otherwise.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointer.

        **Restrictions:** None.

    ..  sw-ifelement:: NvmServiceUnit_ComputeCrc()
        :id: SWIFE_NVMSERVICE_COMPUTECRC
        :arguments:     return: NvmService_Status_t;    pData: const uint8_t*;    length: uint16_t;    pCrc: uint32_t*;

        Computes a CRC-32 checksum over the provided data buffer.

        **Arguments:**

        - **pData**: Pointer to the data buffer.
        - **length**: Number of bytes to process.
        - **pCrc**: Pointer to receive the computed CRC-32 value.

        **Return values:** BPB_NVM_SERVICE_STATUS_OK on success, BPB_NVM_SERVICE_STATUS_INVALID_PARAM for NULL pointers or zero length.

        **Restrictions:** None.

#################################


Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> ReadWrite : Save/Load
	ReadWrite --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor App
	participant NvmService
	App -> NvmService : Save(key, blob)
	NvmService -> NvmService : Compute CRC
	NvmService --> App : Status
	@enduml


#################################
What is this component about?
#################################

The NVM Service provides higher-level storage for configuration records.


#################################
Static structure
#################################

..  uml:: nvmServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: nvmServiceStateMachine.puml

* Sequence diagram
..  uml:: nvmServiceSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide record storage abstraction on top of NVM driver.

Assumptions and influencing factors:
************************************
* NVM driver exposes read/write/erase primitives.

Solutions list:
***************
Solution 1 - Fixed record slots
Store records in fixed addresses.

Solution 2 - Log-structured storage
Append-only storage with garbage collection.

Solution evaluation:
********************
Fixed slots are simpler and sufficient for low write counts.

Final solution:
****************
Solution 1 selected for simplicity.
