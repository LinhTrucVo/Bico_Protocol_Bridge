#################################
What is this component about?
#################################

The Serial To Digital App handles GPIO and PWM commands received over serial.
It validates requests, drives the GPIO/PWM drivers, and returns formatted responses.


#################################
Static structure
#################################

Files:
* serialToDigitalApp.h
* serialToDigitalAppCfg.h
* serialToDigitalAppUnit.c

..  uml::

	@startuml
	class SerialToDigital_Context
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Processing : Command
	Processing --> Idle : Done
	Processing --> Error : Invalid
	Error --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor Host
	participant SerialToDigital
	participant GPIO
	participant PWM
	Host -> SerialToDigital : Command
	SerialToDigital -> GPIO : Configure/Read/Write
	SerialToDigital -> PWM : Configure/Start/Stop
	SerialToDigital --> Host : Response
	@enduml


#################################
What is this component about?
#################################

The Serial-to-Digital App maps serial commands to GPIO states.


#################################
Static structure
#################################

..  uml:: serialToDigitalAppStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: serialToDigitalAppStateMachine.puml

* Sequence diagram
..  uml:: serialToDigitalAppSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a serial-controlled digital I/O application.

Assumptions and influencing factors:
************************************
* GPIO drivers are available.

Solutions list:
***************
Solution 1 - Direct pin control
Map commands to pin write operations.

Solution 2 - Shadowed outputs
Maintain a local shadow state for safety.

Solution evaluation:
********************
Direct pin control is simplest and sufficient.

Final solution:
****************
Solution 1 selected for simplicity.
