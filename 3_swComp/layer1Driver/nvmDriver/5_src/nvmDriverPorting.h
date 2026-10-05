// Port interface of the NVM driver. Implemented by the device workspace, called by nvmDriverUnit.c.

#ifndef NVMDRIVERPORT_H
#define NVMDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Functions
//============================================================================
// The storage is byte addressable, addresses are offsets from the start of the storage.
// Erased bytes read as 0xFF.
bool NvmPort_Init(void);
void NvmPort_DeInit(void);
bool NvmPort_Read(uint32_t offset, uint8_t *pData, uint32_t length);
bool NvmPort_Write(uint32_t offset, const uint8_t *pData, uint32_t length);
bool NvmPort_Erase(uint32_t offset, uint32_t length);

#endif /* NVMDRIVERPORT_H */
