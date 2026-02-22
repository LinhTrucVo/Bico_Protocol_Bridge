deserializeCfg.h
########################

Defines compile-time feature flags for the Deserialize service:

- ``DESERIALIZE_CFG_ENABLE_CRC_CHECK``: Enables CRC-16 verification of incoming frames.
- ``DESERIALIZE_CFG_ENABLE_FRAME_VALIDATION``: Enables structural frame validation (start byte, length, command ID).

..  doxygenfile::  deserializeCfg.h
    :project: Deserialize
