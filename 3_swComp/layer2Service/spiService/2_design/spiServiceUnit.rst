..  c:namespace:: SpiService

SpiServiceUnit.c
###########################

Application layer component providing SPI master write and transceive operations. Called
by the Central Application Controller for RID 0x0500 (SPI Write) and RID 0x0501
(SPI Transceive). Delegates to the SPI master driver for hardware access.

..  doxygenfile:: SpiServiceUnit.c
    :project: SpiService