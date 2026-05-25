Serialize
#########

Layer 2: Service Layer

This function builds UDS (ISO 14229) response frames from internal data structures for transmission.

Description
***********
The Serialize function (UDS response builder) takes structured data objects
from the application layer and encodes them into UDS-compliant response frames
for transmission via the serial driver.

Supported services:

- **SID 0x22** ReadDataByIdentifier → positive response ``0x62`` + DID (2 bytes) + data payload
- **SID 0x2E** WriteDataByIdentifier → positive response ``0x6E`` + DID (2 bytes)
- **SID 0x31** RoutineControl → positive response ``0x71`` + routineControlType + routineID (2 bytes) + status
- **Negative response** ``0x7F`` + requestSID + NRC (applied to all services)

Key responsibilities:
- Encode response SID (requestSID + 0x40)
- Encode DID or RoutineIdentifier (2 bytes, big-endian)
- Append data payload for read responses
- Build negative response frames with NRC code
- Deliver complete byte frame to Serial Driver

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
- Encoding time: < 500 µs per response
- Supports response rates up to 1000 responses/sec

Resource consumption
********************
- RAM: ~256 bytes for response buffers
- ROM: ~2 KB for encoder code
- CPU: Minimal, byte manipulation
