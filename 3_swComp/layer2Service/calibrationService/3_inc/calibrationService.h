// CalibrationService - Public Interface

#ifndef CALIBRATION_SERVICE_H
#define CALIBRATION_SERVICE_H

#include <stdint.h>
#include <stdbool.h>
#include "calibrationServiceCfg.h"
#include "calibrationServiceUnit.h"

typedef enum
{
    CALIBRATION_SERVICE_STATUS_OK = 0,
    CALIBRATION_SERVICE_STATUS_ERROR,
    CALIBRATION_SERVICE_STATUS_BUSY
} CalibrationService_Status_t;

CalibrationService_Status_t CalibrationService_Init(void);
CalibrationService_Status_t CalibrationService_Process(void);
CalibrationService_Status_t CalibrationService_DeInit(void);

#endif /* CALIBRATION_SERVICE_H */
