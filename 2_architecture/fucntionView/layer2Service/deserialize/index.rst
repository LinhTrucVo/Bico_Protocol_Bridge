Deserialize
###########

Layer 2: Service Layer

This function parses incoming UDS (ISO 14229) request frames and converts them into structured data objects.

Description
***********
The Deserialize function (UDS request parser) receives a raw byte stream from the
serial driver and decodes it as a UDS request frame, extracting the service identifier,
data identifier, and payload for processing by the application layer.

Supported services:

- **SID 0x22** ReadDataByIdentifier: extract DID (2 bytes)
- **SID 0x2E** WriteDataByIdentifier: extract DID (2 bytes) + data payload
- **SID 0x31** RoutineControl: extract routineControlType (1 byte) + routineIdentifier (2 bytes) + optional parameters

Key responsibilities:
- Extract and validate SID from incoming frame
- Decode DID or RoutineIdentifier (2 bytes, big-endian)
- Extract data payload for write requests
- Detect unsupported SIDs and malformed frames
- Provide parsed UDS request objects to application layer

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
- Parsing time: < 1 ms per request
- Supports request rates up to 1000 requests/sec

Resource consumption
********************
- RAM: ~256 bytes for receive buffers
- ROM: ~2 KB for parser code
- CPU: Minimal, byte manipulation
