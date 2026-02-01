.. ADC Driver Component Design

Component Overview
******************

The ADC Driver component provides hardware abstraction for ADC operations.
It manages ADC initialization, channel configuration, conversion start, and result reading.

Component Architecture
**********************

The component consists of:
- adcDriver.h: Public interface
- adcDriverUnit.c: Implementation
- adcDriverCfg.h: Configuration parameters

Design Decisions
****************

- The driver uses a state machine to track initialization and conversion states
- Channel validation is performed before all operations
- The driver maintains a context structure for runtime state management
- Vendor-specific HAL calls are marked with TODO for later implementation
