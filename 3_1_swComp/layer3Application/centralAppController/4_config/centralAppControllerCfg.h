#ifndef BPB_CENTRAL_APP_CONTROLLER_CFG_H
#define BPB_CENTRAL_APP_CONTROLLER_CFG_H

//============================================================================
// Configuration - Feature Enable/Disable Flags
//============================================================================
#define BPB_CENTRAL_APP_CFG_ENABLE_ERROR_LOGGING  true
#define BPB_CENTRAL_APP_CFG_ENABLE_STATE_MACHINE  true

//============================================================================
// Configuration - Frame Delimiters
//============================================================================
#define BPB_CENTRAL_APP_CFG_FRAME_PREFIX         (0x5555U)
#define BPB_CENTRAL_APP_CFG_FRAME_POSTFIX        (0xAAAAU)

#define BPB_CENTRAL_APP_CFG_FRAME_PREFIX_HIGH    ((uint8_t)((BPB_CENTRAL_APP_CFG_FRAME_PREFIX >> 8U) & 0xFFU))
#define BPB_CENTRAL_APP_CFG_FRAME_PREFIX_LOW     ((uint8_t)(BPB_CENTRAL_APP_CFG_FRAME_PREFIX & 0xFFU))
#define BPB_CENTRAL_APP_CFG_FRAME_POSTFIX_HIGH   ((uint8_t)((BPB_CENTRAL_APP_CFG_FRAME_POSTFIX >> 8U) & 0xFFU))
#define BPB_CENTRAL_APP_CFG_FRAME_POSTFIX_LOW    ((uint8_t)(BPB_CENTRAL_APP_CFG_FRAME_POSTFIX & 0xFFU))

#define BPB_CENTRAL_APP_CFG_FRAME_DELIMITER_SIZE (2U)

#endif /* BPB_CENTRAL_APP_CONTROLLER_CFG_H */
