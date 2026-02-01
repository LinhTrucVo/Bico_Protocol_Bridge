I2C Master Driver
#################

Layer 1: Driver Layer

This function provides I2C master mode driver interface, wrapping vendor HAL for I2C communication as a bus master.

Description
***********
The I2C Master Driver manages I2C bus initialization, configuration, and master-mode transactions. 
It provides interface for reading from and writing to I2C slave devices.

Key responsibilities:
- Initialize and configure I2C peripheral in master mode
- Perform I2C write transactions to slave devices
- Perform I2C read transactions from slave devices
- Handle I2C bus errors (NACK, timeout, arbitration loss)
- Scan I2C bus for connected devices

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
- I2C clock speed: 100 kHz (standard), 400 kHz (fast), 1 MHz (fast plus)
- Transaction timeout: configurable (default 1000ms)
- Typical transaction time: 1-10ms depending on data size

Resource consumption
********************
- RAM: ~128 bytes for control structures
- ROM: ~1.5 KB for driver code
- CPU: Event-driven, minimal overhead
