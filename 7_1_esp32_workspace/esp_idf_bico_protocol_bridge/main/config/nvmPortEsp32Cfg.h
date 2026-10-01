// Hardware configuration of the ESP32 NVM port. The storage is kept in NVS as fixed size chunks.

#ifndef NVMPORTESP32CFG_H
#define NVMPORTESP32CFG_H

// NVS namespace, at most 15 characters.
#ifndef BICO_PROTOCOL_BRIDGE_NVM_NAMESPACE
#define BICO_PROTOCOL_BRIDGE_NVM_NAMESPACE      "bico_pb_nvm"
#endif

// Size of one NVS blob that holds a part of the storage.
#ifndef BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE
#define BICO_PROTOCOL_BRIDGE_NVM_CHUNK_SIZE     256U
#endif

#endif /* NVMPORTESP32CFG_H */
