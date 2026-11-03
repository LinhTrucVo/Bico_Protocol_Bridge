Serial To Digital I/O
#####################

.. What is Feature:
.. Characteristics or capabilities that a product offers to users
.. Focuses on value and benefits delivered
.. Answers: "What's special about it? What do users gain?"
.. Example: 108MP camera, 120Hz display, 65W fast charging, IP68 water resistance

With Serial to Digital I/O, users can seamlessly control digital signals and PWM outputs 
using simple serial communication protocols, enabling easy interfacing with digital devices and actuators.

User benefits
****************
Users can quickly and easily control digital devices, sensors, and actuators through serial commands 
without complex programming or additional hardware.
PWM capabilities enable precise control of motors, LEDs, and other analog-like devices.
This simplifies prototyping, testing, and development, saving time and effort.
..  uml:: userBenefit.puml

Use case
*****************
When a user wants to control digital outputs (like LEDs, relays, or GPIO pins) or read digital inputs (like buttons or sensors),
or generate PWM signals for motor speed control or LED brightness adjustment,
the user can use the Serial to Digital I/O to easily configure and control these devices via serial commands 
without writing embedded code.
..  uml:: useCase.puml

Supported functions include:
- Digital I/O configuration (pin mode: input/output, pull-up/pull-down resistors).
- Configuration persistence in non-volatile storage (users do not need to reconfigure after power cycle).
- Digital signal write (set high/low output states).
- Digital signal read (read input pin states).
- PWM output configuration (frequency, duty cycle, resolution).
- PWM signal generation for motor control, LED dimming, and analog signal emulation.

Verification criteria
*********************
- Successful configuration of digital I/O pins via serial commands.
- Accurate digital signal read/write operations.
- Configuration persistence after power cycle.
- Successful PWM configuration (frequency, duty cycle) via serial commands.
- PWM output signal matches configured parameters (measured with oscilloscope).
