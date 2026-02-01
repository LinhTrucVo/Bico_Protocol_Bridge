Calibration Service
###################

Layer 2: Service Layer

This function provides calibration management service for analog inputs, 
supporting offset and gain adjustments per channel.

Description
***********
The Calibration Service manages calibration parameters for ADC channels, 
applying offset and gain corrections to raw ADC values. 
It stores calibration data persistently and provides calibration procedures.

Key responsibilities:
- Store and load calibration parameters (offset, gain) per channel
- Apply calibration to raw ADC values
- Perform calibration procedures (single-point, two-point)
- Validate calibration parameters
- Provide factory calibration defaults

Static view
***********
..  uml:: staticView.puml

Information flow
****************
..  uml:: informationFlow.puml

Dynamic behaviour
*****************
..  uml:: dynamicBehaviour.puml

Timing behaviour
****************
- Calibration apply time: < 100 µs per sample
- Calibration save time: < 50 ms
- Accuracy: ±0.5% of full scale after calibration

Resource consumption
********************
- RAM: ~256 bytes for calibration data
- ROM: ~1.5 KB for service code
- NVM: 256 bytes for persistent calibration storage
