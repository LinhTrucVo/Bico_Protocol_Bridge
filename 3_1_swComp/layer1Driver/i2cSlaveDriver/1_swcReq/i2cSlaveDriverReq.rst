.. Descrive about the I2C Slave Driver component requirements
Overall requirements
********************

The I2C Slave Driver shall provide a hardware abstraction for I2C slave mode operation.
The component shall support address configuration and buffered TX/RX handling.

Input validation
****************

The component shall validate addresses, buffer pointers, and lengths.
The component shall reject buffer sizes exceeding the maximum supported length.

Requirements for component
**************************

Req-i2cSlaveDriver-001: The component shall initialize the I2C slave with a configuration structure.
   Verification: Init returns OK for valid configuration values.

Req-i2cSlaveDriver-002: The component shall set and get the slave address.
   Verification: SetAddress and GetAddress return the configured address.

Req-i2cSlaveDriver-003: The component shall provide RX and TX buffer configuration APIs.
   Verification: SetRxBuffer and SetTxBuffer accept valid buffers and lengths.

Req-i2cSlaveDriver-004: The component shall report received length after a master write.
   Verification: GetRxLength returns the correct received length.

Req-i2cSlaveDriver-005: The component shall support callbacks for RX, TX, and address match events.
   Verification: Callbacks are invoked on corresponding events.

Variant Handling
****************

The component supports multiple hardware variant implementations through the CMake ``L1_VARIANT``
build variable. The file ``i2cSlaveDriverUnitEsp32.c`` provides the ESP32-specific implementation
of the driver interface and is compiled instead of the default ``i2cSlaveDriverUnit.c`` when
``L1_VARIANT`` is set to ``Esp32``.
The public interface defined in ``i2cSlaveDriverUnit.h`` remains unchanged across all variants,
ensuring API consistency for all upper layers.

