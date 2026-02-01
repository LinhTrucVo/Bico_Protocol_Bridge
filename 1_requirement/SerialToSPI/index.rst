Serial To SPI Architecture
##########################

.. What is Feature:
.. Characteristics or capabilities that a product offers to users
.. Focuses on value and benefits delivered
.. Answers: "What's special about it? What do users gain?"
.. Example: 108MP camera, 120Hz display, 65W fast charging, IP68 water resistance

With Serial to SPI Architecture, users can seamlessly convert serial data into SPI format, 
from that the user can interface with SPI-based devices using simple serial communication protocols.

Supported functions include:
- SPI Parameter configuration (can save in non-volatile storage, from that user does not need to reconfigure after power cycle).
- Data transmission from Serial to SPI.
- Data reception from SPI to Serial.

User benefits
****************
User can quickly and easily connect serial devices to SPI peripherals (sensor, actuator, etc.) 
without complex wiring or additional hardware.
This simplifies prototyping and development, saving time and effort.
..  uml:: userBenefit.puml

Use case
*****************
When a user wants to connect a serial device (like a microcontroller or sensor) to an SPI peripheral (like an SPI-based display or memory chip),
the user can use the Serial to SPI Architecture to facilitate communication between the two devices easily without programming complexity.
..  uml:: useCase.puml

Verification criteria
*********************
- Successful configuration of SPI parameters via serial commands.
- Configuration persistence after power cycle.
- Accurate data transmission from Serial to SPI and vice versa.