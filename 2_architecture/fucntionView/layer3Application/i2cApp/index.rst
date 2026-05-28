I2C App
###############

Layer 3: Application Layer

This application implements the Serial to I2C bridge functionality, managing I2C communication in both master and slave modes.

Description
***********
The I2C App provides complete I2C communication functionality including 
master and slave mode operations, device management, and data transfer. 
It implements the requirements from the I2C feature specification.

Key responsibilities:
- Manage I2C master mode operations (write, read, scan)
- Manage I2C slave mode operations (respond to master)
- Only 1 mode (master/slave) active at a time
- Handle I2C configuration (clock speed, addressing)
- Implement I2C error handling and recovery
- Support multiple I2C transactions
- Persist I2C configuration in NVM

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
- Command response: < 10 ms
- I2C transaction: 1-50 ms (depends on data size)
- Bus scan: < 2 seconds (all addresses)
- Configuration save: < 100 ms

Resource consumption
********************
- RAM: ~512 bytes for I2C buffers
- ROM: ~3 KB for application code
- NVM: ~256 bytes for configuration
