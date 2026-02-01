// Serialize - Public Interface

#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <stdint.h>
#include <stdbool.h>
#include "serializeCfg.h"
#include "serializeUnit.h"

typedef enum
{
    SERIALIZE_STATUS_OK = 0,
    SERIALIZE_STATUS_ERROR,
    SERIALIZE_STATUS_BUSY
} Serialize_Status_t;

Serialize_Status_t Serialize_Init(void);
Serialize_Status_t Serialize_Process(void);
Serialize_Status_t Serialize_DeInit(void);

#endif /* SERIALIZE_H */
