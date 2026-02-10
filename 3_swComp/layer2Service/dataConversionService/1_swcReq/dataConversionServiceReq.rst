.. Descrive about the Data Conversion Service component requirements
Overall requirements
********************

The Data Conversion Service shall convert ADC raw values into engineering units using per-channel configuration.
The component shall support voltage and percentage conversions.

Input validation
****************

The component shall validate channel IDs, resolution bits, and reference voltage values.
The component shall reject null pointers for output values or configuration.

Requirements for component
**************************

Req-dataConversionService-001: The component shall store conversion configuration per channel.
   Verification: SetChannelConfig stores and GetChannelConfig returns the same configuration.

Req-dataConversionService-002: The component shall convert raw values to voltage using vRef and resolution.
   Verification: ConvertRawToVoltage returns correct voltage for reference values.

Req-dataConversionService-003: The component shall convert raw values using per-channel scaling and offset.
   Verification: Convert outputs correct value for configured scale and offset.

Req-dataConversionService-004: The component shall support conversion to percentage units.
   Verification: Convert returns percent values between 0 and 100 for valid inputs.

Req-dataConversionService-005: The component shall return INVALID_PARAM for out-of-range channel IDs.
   Verification: APIs return INVALID_PARAM for invalid channel IDs.
