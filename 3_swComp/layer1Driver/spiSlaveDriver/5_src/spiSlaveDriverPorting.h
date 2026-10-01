// Port interface of the SPI slave driver. Implemented by the device workspace, called by spiSlaveDriverUnit.c.

#ifndef SPISLAVEDRIVERPORT_H
#define SPISLAVEDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Macros
//============================================================================
// Largest transfer the port can queue.
#define SPISLAVEPORT_MAX_TRANSFER_SIZE  512U

//============================================================================
// Public Types
//============================================================================
// Called by the port, possibly from interrupt context, when the chip select is asserted (true) or released (false).
typedef void (*SpiSlavePort_SelectHandler_t)(bool selected);

// Called by the port from task context when a queued transfer is finished.
typedef void (*SpiSlavePort_TransferHandler_t)(const uint8_t *pRxData, uint16_t length);

//============================================================================
// Public Functions
//============================================================================
// mode is the SPI mode 0..3.
bool SpiSlavePort_Init(uint8_t mode, bool lsbFirst);
void SpiSlavePort_DeInit(void);
// Queues one transfer of maxLength bytes. The first txLength bytes of the answer come from pTxData, the rest is zero.
// Returns false when the previous transfer is still pending.
bool SpiSlavePort_QueueTransfer(const uint8_t *pTxData, uint16_t txLength, uint16_t maxLength);
void SpiSlavePort_SetSelectHandler(SpiSlavePort_SelectHandler_t handler);
void SpiSlavePort_SetTransferHandler(SpiSlavePort_TransferHandler_t handler);

#endif /* SPISLAVEDRIVERPORT_H */
