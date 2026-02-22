serializeCfg.h
########################

Defines compile-time feature flags for the Serialize service:

- ``SERIALIZE_CFG_ENABLE_CRC_GENERATION``: Enables CRC-16 computation and appending to outgoing frames.
- ``SERIALIZE_CFG_ENABLE_FRAME_FORMATTING``: Enables full frame formatting (start byte, length, payload, CRC).

..  doxygenfile::  serializeCfg.h
    :project: Serialize
