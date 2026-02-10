.. Descrive about the Calibration Service component requirements
Overall requirements
********************

The Calibration Service shall manage per-channel gain and offset calibration data.
The component shall apply calibration to raw measurements and support persistence in NVM.

Input validation
****************

The component shall validate channel IDs and pointer parameters before use.
The component shall reject calibration data that results in invalid gain or NaN values.

Requirements for component
**************************

Req-calibrationService-001: The component shall store calibration gain and offset per channel.
   Verification: SetCalibration stores data and GetCalibration returns the same values.

Req-calibrationService-002: The component shall apply calibration to input values.
   Verification: Apply returns output = (input + offset) * gain for valid channel.

Req-calibrationService-003: The component shall compute calibration from two-point references.
   Verification: ComputeTwoPoint produces correct gain and offset for reference data.

Req-calibrationService-004: The component shall clear calibration for a channel or all channels.
   Verification: ClearCalibration resets valid flag and default values.

Req-calibrationService-005: The component shall save and load calibration data to NVM.
   Verification: SaveToNvm and LoadFromNvm persist values across reset.

Req-calibrationService-006: The component shall return INVALID_PARAM for null pointers.
   Verification: APIs return INVALID_PARAM for null input pointers.
