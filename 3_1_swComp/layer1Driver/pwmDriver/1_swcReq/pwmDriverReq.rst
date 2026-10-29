.. Descrive about the PWM Driver component requirements
Overall requirements
********************

The PWM Driver shall provide a hardware abstraction for PWM channel configuration and control.
The component shall support frequency, duty cycle, and polarity configuration.

Input validation
****************

The component shall validate channel IDs, frequency, and duty-cycle ranges.
The component shall reject operations when the driver is not initialized.

Requirements for component
**************************

Req-pwmDriver-001: The component shall initialize the PWM peripheral.
   Verification: Init returns OK when the PWM hardware is ready.

Req-pwmDriver-002: The component shall configure PWM channels with frequency and duty cycle.
   Verification: ConfigureChannel applies the requested settings for valid channels.

Req-pwmDriver-003: The component shall allow updating frequency and duty cycle.
   Verification: SetFrequency and SetDutyCycle update parameters within range.

Req-pwmDriver-004: The component shall start and stop PWM outputs.
   Verification: StartChannel enables output and StopChannel disables output.

Req-pwmDriver-005: The component shall report channel running status and configuration.
   Verification: IsChannelRunning and GetConfiguration return correct values.

Variant Handling
****************

The component supports multiple hardware variant implementations through the CMake ``L1_VARIANT``
build variable. The file ``pwmDriverUnitEsp32.c`` provides the ESP32-specific implementation
of the driver interface and is compiled instead of the default ``pwmDriverUnit.c`` when
``L1_VARIANT`` is set to ``Esp32``.
The public interface defined in ``pwmDriverUnit.h`` remains unchanged across all variants,
ensuring API consistency for all upper layers.

