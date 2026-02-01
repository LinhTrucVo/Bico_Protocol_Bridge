Deserialize
###########

Layer 2: Service Layer

This function parses incoming serial stream data and converts it into structured data objects.

Description
***********
The Deserialize function (command parser) receives raw serial stream data and 
parses it into structured data objects that can be processed by the application layer. 
It handles command syntax, parameter extraction, and error detection.

Key responsibilities:
- Parse incoming serial command strings
- Extract command type and parameters
- Validate command syntax
- Convert serial stream to internal data structures
- Handle different command formats
- Detect parsing errors
- Provide parsed data objects to application layer

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
- Parsing time: < 1 ms per command
- Supports command rates up to 1000 commands/sec
- Buffer processing: Real-time

Resource consumption
********************
- RAM: ~256 bytes for formatting buffers
- ROM: ~2 KB for formatter code
- CPU: Minimal, string formatting
