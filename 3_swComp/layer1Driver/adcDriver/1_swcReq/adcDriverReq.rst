.. Descrive about the ADC Driver component requirements
Overall requirements
********************

The ADC Driver shall provide a hardware abstraction for ADC initialization, configuration, and sampling.
The component shall support multiple channels, selectable resolution, and sampling frequency control.

Input validation
****************

The component shall validate channel IDs, configuration pointers, parameter ranges, supported resolutions, and sampling frequencies. Invalid parameters shall be rejected.

Requirements for component
**************************

Req-adcDriver-001: The component shall initialize the ADC peripheral with a configuration structure.
   Verification: Init returns OK for valid configuration and ERROR for invalid parameters.

Req-adcDriver-002: The component shall enable or disable ADC channels.
   Verification: ConfigureChannel enables and disables channels as requested.

Req-adcDriver-003: The component shall start and stop conversions for a selected channel.
   Verification: StartConversion initiates and StopConversion halts conversions.

Req-adcDriver-004: The component shall read a conversion result for a channel.
   Verification: ReadValue returns a valid sample within the configured resolution range.

Req-adcDriver-005: The component shall allow configuration of sampling frequency.
   Verification: SetSamplingFrequency accepts values in the supported range.

Req-adcDriver-006: The component shall provide conversion-complete status and callback support.
   Verification: IsConversionComplete and callback are invoked on completion.

Variant Handling
****************

The component supports multiple hardware variant implementations through the CMake ``L1_VARIANT``
build variable. The file ``adcDriverUnitEsp32.c`` provides the ESP32-specific implementation
of the driver interface and is compiled instead of the default ``adcDriverUnit.c`` when
``L1_VARIANT`` is set to ``Esp32``.
The public interface defined in ``adcDriverUnit.h`` remains unchanged across all variants,
ensuring API consistency for all upper layers.

