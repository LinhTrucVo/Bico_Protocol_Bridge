.. Describe about the Central App Controller component requirements
Overall requirements
********************

The Central App Controller shall be the sole owner of all DID and RID definitions in the system.
It shall dispatch UDS requests (SID 0x22, 0x2E, 0x31) to downstream services using typed API calls.
Downstream modules (ConfigService, peripheral apps) have no UDS/DID/RID awareness.

Input validation
****************

The component shall validate incoming UDS request frames via the Deserialize service.
The component shall reject unsupported SIDs with NRC 0x11 (serviceNotSupported).
The component shall reject unknown DIDs/RIDs with NRC 0x31 (requestOutOfRange).
The component shall reject insufficient payload length with NRC 0x13 (incorrectMessageLength).

Requirements for component
**************************

Req-centralAppController-001: The component shall initialize all dependent services and applications on startup.
   Verification: Init sequence invokes Deserialize, Serialize, ConfigService, and all peripheral app Init.

Req-centralAppController-002: The component shall dispatch SID 0x22 (ReadDataByIdentifier) to ConfigService getters.
   Verification: DID 0x1001 returns ADC sample rate, DID 0x1002 returns ADC resolution.

Req-centralAppController-003: The component shall dispatch SID 0x2E (WriteDataByIdentifier) to ConfigService setters.
   Verification: DID 0x1001 with payload sets ADC sample rate; invalid value returns NRC 0x31.

Req-centralAppController-004: The component shall dispatch SID 0x31 RID 0x0100 to AnalogApp_ReadAdc.
   Verification: Routine response contains raw ADC value for specified channel.

Req-centralAppController-005: The component shall dispatch SID 0x31 RID 0x0200/0x0201 to DigitalApp GPIO operations.
   Verification: GPIO write/read executes on specified pin and returns result.

Req-centralAppController-006: The component shall dispatch SID 0x31 RID 0x0300/0x0301 to DigitalApp PWM operations.
   Verification: PWM start/stop executes on specified channel.

Req-centralAppController-007: The component shall dispatch SID 0x31 RID 0x0400/0x0401 to I2CApp Write/Read.
   Verification: I2C operations execute with specified address and data.

Req-centralAppController-008: The component shall dispatch SID 0x31 RID 0x0500/0x0501 to SPIApp Write/Transceive.
   Verification: SPI operations execute with specified device and data.

Req-centralAppController-009: The component shall build positive UDS responses via Serialize service.
   Verification: Positive responses contain correct response SID (request+0x40), identifier, and data.

Req-centralAppController-010: The component shall build negative UDS responses (0x7F) for all error conditions.
   Verification: Negative responses contain [0x7F, requestSID, NRC] with appropriate NRC code.

Req-centralAppController-011: The component shall report errors via registered callback if configured.
   Verification: Error callback invoked with NRC code on processing failure.