// Deserialize - Public Interface

#ifndef DESERIALIZE_H
#define DESERIALIZE_H

#include <stdint.h>
#include <stdbool.h>
#include "deserializeCfg.h"
#include "deserializeUnit.h"

typedef enum
{
    DESERIALIZE_STATUS_OK = 0,
    DESERIALIZE_STATUS_ERROR,
    DESERIALIZE_STATUS_BUSY
} Deserialize_Status_t;

Deserialize_Status_t Deserialize_Init(void);
Deserialize_Status_t Deserialize_Process(void);
Deserialize_Status_t Deserialize_DeInit(void);

#endif /* DESERIALIZE_H */
