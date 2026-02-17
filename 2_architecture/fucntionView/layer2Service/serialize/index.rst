Serialize
#########

Layer 2: Service Layer

This function converts internal data structures into serial stream format for transmission.

Description
***********
The Serialize function (response formatter) takes structured raw data objects 
from the application layer and converts them into serial stream format for transmission. 
It handles different output formats and ensures proper message framing.

Key responsibilities:
- Convert internal raw data structures to serial stream format
- Format raw data (ADC values, digital states, etc.) for serial output
- Apply message framing and delimiters
- Support multiple output formats (ASCII, HEX, binary)
- Handle error response formatting
- Generate status messages for transmission
- No physical unit conversion (e.g., no voltage/current calculations)

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
- Formatting time: < 500 µs per response
- Supports response rates up to 1000 responses/sec
- Real-time formatting

Resource consumption
********************
- RAM: ~256 bytes for parsing buffers
- ROM: ~2 KB for parser code
- CPU: Minimal, string processing
