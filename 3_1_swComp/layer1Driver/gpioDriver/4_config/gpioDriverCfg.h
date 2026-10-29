// GPIO Driver Configuration
// This file contains feature enable/disable flags for the GPIO driver

#ifndef BPB_GPIODRIVERCFG_H
#define BPB_GPIODRIVERCFG_H

//============================================================================
// Configuration - Feature Enable/Disable Flags
//============================================================================
#define BPB_GPIO_CFG_ENABLE_INTERRUPTS       true
#define BPB_GPIO_CFG_ENABLE_CALLBACKS        true
#define BPB_GPIO_STATUS_INVALID_MODE     GPIOSTATUS_INVALID_MODE
#define BPB_GPIO_STATUS_NOT_INITIALIZED  GPIOSTATUS_NOT_INITIALIZED

#endif /* BPB_GPIODRIVERCFG_H */
