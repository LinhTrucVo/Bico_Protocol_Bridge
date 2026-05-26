..  c:namespace:: SerialToSPIApp

serialToSPIAppUnit.c
###########################

Application layer component providing SPI master write and transceive operations. Called
by the Central Application Controller for RID 0x0501 (SPI Write) and RID 0x0502
(SPI Transceive). Delegates to the SPI master driver for hardware access.

..  doxygenfile:: serialToSPIAppUnit.c
    :project: SerialToSPIApp