..  c:namespace:: SerialToI2CApp

serialToI2CAppUnit.c
###########################

Application layer component providing I2C master write and read operations. Called by
the Central Application Controller for RID 0x0400 (I2C Write) and RID 0x0401 (I2C Read).
Delegates to the I2C master driver for hardware access.

..  doxygenfile:: serialToI2CAppUnit.c
    :project: SerialToI2CApp