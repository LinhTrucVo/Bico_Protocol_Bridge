deserializeCfg.h
########################

Defines compile-time feature flags for the Deserialize service:

- ``DESERIALIZE_CFG_ENABLE_CRC_CHECK``: Reserved for future transport-level CRC (not used in UDS parsing layer).
- ``DESERIALIZE_CFG_ENABLE_FRAME_VALIDATION``: Enables structural frame validation (minimum length, SID range).

..  doxygenfile::  deserializeCfg.h
    :project: Deserialize