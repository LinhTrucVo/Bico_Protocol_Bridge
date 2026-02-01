NVM Driver
###########

Layer 1: Driver Layer

This function provides NVM (Non-Volatile Memory) driver interface, wrapping vendor HAL for persistent data storage operations.

Description
***********
The NVM Driver manages non-volatile memory (EEPROM, Flash, etc.) operations including read, write, and erase. 
It provides interface for storing configuration data that persists across power cycles.

Key responsibilities:
- Initialize and configure NVM hardware
- Write data to non-volatile memory
- Read data from non-volatile memory
- Erase memory sectors/pages
- Handle memory access errors
- Implement write protection mechanisms

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
- Read operation: < 1 ms
- Write operation: 5-50 ms (depends on technology)
- Erase operation: 20-100 ms per sector
- Endurance: 100K-1M write cycles (typical)

Resource consumption
********************
- RAM: ~64 bytes for control structures
- ROM: ~1 KB for driver code
- CPU: Blocking during write/erase operations
