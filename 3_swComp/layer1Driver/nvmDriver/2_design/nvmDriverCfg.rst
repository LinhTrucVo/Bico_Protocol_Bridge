nvmDriverCfg.h
########################

Defines compile-time feature flags for the NVM Driver:

- ``BPB_NVM_CFG_ENABLE_WRITE_PROTECTION``: Enables hardware write-protection support.
- ``BPB_NVM_CFG_ENABLE_CRC_VERIFY``: Enables CRC-based data verification after write operations.
- ``BPB_NVM_CFG_ENABLE_CALLBACKS``: Enables operation-complete callback registration.

..  doxygenfile::  nvmDriverCfg.h
    :project: NvmDriver
