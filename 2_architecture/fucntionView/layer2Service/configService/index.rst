Configuration Service
#####################

Layer 2: Service Layer

This function provides configuration management service for storing, retrieving, and validating system configuration parameters.

Description
***********
The Configuration Service manages all system configuration parameters, 
providing a unified interface for configuration storage, retrieval, validation, and default settings management. 
It works with the NVM Driver to persist configurations across power cycles.

Key responsibilities:
- Provide typed Get/Set API for each configuration parameter (no DID/RID awareness)
- Validate parameter ranges internally on Set calls
- Store configuration parameters to non-volatile memory as JSON
- Load configuration parameters from non-volatile memory on startup
- Provide default configuration values when NVM is empty or corrupt
- Manage configuration versioning

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
- Configuration load time: < 10 ms
- Configuration save time: < 50 ms
- Validation time: < 1 ms

Resource consumption
********************
- RAM: ~512 bytes for configuration buffer
- ROM: ~2 KB for service code
- NVM: 1-4 KB for configuration storage
