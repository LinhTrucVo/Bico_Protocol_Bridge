Data Conversion Service
######################

Layer 2: Service Layer

This function provides data conversion and formatting service for converting between raw values, engineering units, and various data formats.

Description
***********
The Data Conversion Service handles conversion between different data representations including raw ADC values to engineering units (voltage, temperature, pressure), format conversions (binary, ASCII, hexadecimal), and unit conversions.

Key responsibilities:
- Convert raw ADC values to engineering units
- Apply scaling and unit conversions
- Convert between binary, ASCII, and hexadecimal formats
- Handle endianness conversions
- Format data for serial transmission (binary, JSON, ASCII, HEX, etc.)

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
- Conversion time: < 50 µs per value
- Format conversion: < 100 µs
- Minimal impact on system performance

Resource consumption
********************
- RAM: ~128 bytes for conversion buffers
- ROM: ~2 KB for service code
- CPU: Computational, minimal overhead
