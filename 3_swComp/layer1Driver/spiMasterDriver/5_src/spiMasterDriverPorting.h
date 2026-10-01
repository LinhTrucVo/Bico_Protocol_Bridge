// Port interface of the SPI master driver. Implemented by the device workspace, called by spiMasterDriverUnit.c.

#ifndef SPIMASTERDRIVERPORT_H
#define SPIMASTERDRIVERPORT_H

//============================================================================
// Dependencies
//============================================================================
#include <stdint.h>
#include <stdbool.h>

//============================================================================
// Public Functions
//============================================================================
// mode is the SPI mode 0..3. Chip select is controlled by the hardware and asserted for each transfer.
bool SpiMasterPort_Init(uint32_t clockHz, uint8_t mode, bool lsbFirst);
void SpiMasterPort_DeInit(void);
bool SpiMasterPort_Configure(uint32_t clockHz, uint8_t mode, bool lsbFirst);
// Blocking full duplex transfer. pTxData or pRxData may be NULL when only one direction is needed.
bool SpiMasterPort_Transfer(const uint8_t *pTxData, uint8_t *pRxData, uint16_t length);
// Keeps chip select asserted between transfers until the bus is released.
bool SpiMasterPort_AcquireBus(void);
void SpiMasterPort_ReleaseBus(void);

#endif /* SPIMASTERDRIVERPORT_H */
