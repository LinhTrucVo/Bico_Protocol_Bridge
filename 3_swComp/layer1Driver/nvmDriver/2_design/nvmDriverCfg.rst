nvmDriverCfg.h
########################

Defines compile-time feature flags for the NVM Driver:

- ``NVM_CFG_ENABLE_WRITE_PROTECTION``: Enables hardware write-protection support.
- ``NVM_CFG_ENABLE_CRC_VERIFY``: Enables CRC-based data verification after write operations.
- ``NVM_CFG_ENABLE_CALLBACKS``: Enables operation-complete callback registration.

..  doxygenfile::  nvmDriverCfg.h
    :project: NvmDriver
