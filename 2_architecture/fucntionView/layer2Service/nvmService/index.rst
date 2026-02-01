NVM Service
###########

Layer 2: Service Layer

This function provides high-level NVM (Non-Volatile Memory) service with data integrity checking, wear leveling, and memory management.

Description
***********
The NVM Service provides higher-level non-volatile memory management beyond basic read/write operations. 
It can operate in two modes:

1. **Direct NVM Mode**: Implements integrity checking (CRC), wear leveling, memory layout management, and safe write operations on raw NVM.
2. **File System Wrapper Mode**: Some vendors provide file system abstraction for NVM (e.g., LittleFS, FatFS). This service can wrap those APIs to provide a uniform interface.

Key responsibilities:
- Provide safe write operations with integrity checking (Direct Mode) or file operations wrapper (File System Mode)
- Implement CRC/checksum validation for stored data (Direct Mode)
- Manage memory layout and addressing (Direct Mode) or wrap file system APIs (File System Mode)
- Implement wear leveling algorithms (Direct Mode, if applicable)
- Handle memory full conditions
- Provide data versioning support
- Abstract storage interface - applications use same API regardless of underlying implementation

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
- Read with CRC check: < 5 ms
- Write with CRC: < 100 ms
- Memory scan: < 50 ms

Resource consumption
********************
- RAM: ~256 bytes for buffers and CRC calculation
- ROM: ~2 KB for service code
- NVM: Metadata overhead ~5% of total capacity
