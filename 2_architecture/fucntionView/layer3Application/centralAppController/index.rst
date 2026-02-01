Central App Controller
#####################

Layer 3: Application Layer

This function provides centralized control and coordination for all application modules in the system.

Description
***********
The Central App Controller acts as the main coordinator for all application modules (SerialToAnalog, SerialToDigital, SerialToI2C, SerialToSPI). 
It manages initialization, command routing, resource arbitration, and system-level coordination.

Key responsibilities:
- Initialize and coordinate all application modules
- Route commands to appropriate application modules
- Manage resource allocation and arbitration
- Coordinate inter-module communication
- Handle system-level state management
- Manage system startup and shutdown sequences
- Implement watchdog and health monitoring

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
- Command routing: < 100 µs
- System initialization: < 500 ms
- Module coordination: Real-time

Resource consumption
********************
- RAM: ~512 bytes for control structures
- ROM: ~3 KB for controller code
- CPU: Event-driven, coordination overhead ~5%
