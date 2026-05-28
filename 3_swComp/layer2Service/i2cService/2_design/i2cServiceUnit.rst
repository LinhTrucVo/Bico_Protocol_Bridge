..  c:namespace:: I2cService

I2cServiceUnit.c
###########################

Application layer component providing I2C master write and read operations. Called by
the Central Application Controller for RID 0x0400 (I2C Write) and RID 0x0401 (I2C Read).
Delegates to the I2C master driver for hardware access.

..  doxygenfile:: I2cServiceUnit.c
    :project: I2cService