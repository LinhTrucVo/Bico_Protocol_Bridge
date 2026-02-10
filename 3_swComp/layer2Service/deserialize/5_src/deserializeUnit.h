#ifndef DESERIALIZEUNIT_H
#define DESERIALIZEUNIT_H
#include <stdint.h>
#include <stdbool.h>
#include "deserializeCfg.h"
typedef enum Deserialize_Status_t Deserialize_Status_t;
typedef struct Deserialize_Frame_t Deserialize_Frame_t;
typedef struct Deserialize_Request_t Deserialize_Request_t;
Deserialize_Status_t DeserializeUnit_Init(void);
Deserialize_Status_t DeserializeUnit_DeInit(void);
Deserialize_Status_t DeserializeUnit_ValidateFrame(const Deserialize_Frame_t *pFrame);
Deserialize_Status_t DeserializeUnit_ParseFrame(const Deserialize_Frame_t *pFrame, Deserialize_Request_t *pRequest);
Deserialize_Status_t DeserializeUnit_ComputeCrc(const uint8_t *pData, uint16_t length, uint16_t *pCrc);
#endif
