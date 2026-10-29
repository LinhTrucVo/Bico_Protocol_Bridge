.. Descrive about the SPI Slave Driver component requirements
Overall requirements
********************

The SPI Slave Driver shall provide a hardware abstraction for SPI slave transfers.
The component shall support buffered TX/RX and callback-based notifications.

Input validation
****************

The component shall validate buffer pointers and lengths.
The component shall reject buffer sizes exceeding the maximum supported length.

Requirements for component
**************************

Req-spiSlaveDriver-001: The component shall initialize the SPI slave with a configuration structure.
   Verification: Init returns OK for valid configuration values.

Req-spiSlaveDriver-002: The component shall allow setting transmit and receive buffers.
   Verification: SetTxBuffer and SetRxBuffer accept valid buffers and lengths.

Req-spiSlaveDriver-003: The component shall provide received length reporting.
   Verification: GetRxLength returns the correct length after a transfer.

Req-spiSlaveDriver-004: The component shall report selection status by the SPI master.
   Verification: IsSelected reflects the chip select state.

Req-spiSlaveDriver-005: The component shall support RX and TX completion callbacks.
   Verification: Registered callbacks are invoked on corresponding events.

Variant Handling
****************

The component supports multiple hardware variant implementations through the CMake ``L1_VARIANT``
build variable. The file ``spiSlaveDriverUnitEsp32.c`` provides the ESP32-specific implementation
of the driver interface and is compiled instead of the default ``spiSlaveDriverUnit.c`` when
``L1_VARIANT`` is set to ``Esp32``.
The public interface defined in ``spiSlaveDriverUnit.h`` remains unchanged across all variants,
ensuring API consistency for all upper layers.

