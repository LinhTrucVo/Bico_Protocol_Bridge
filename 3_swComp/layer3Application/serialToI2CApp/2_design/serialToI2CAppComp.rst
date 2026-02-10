#################################
What is this component about?
#################################

The Serial To I2C App bridges serial commands to I2C master transactions.
It manages I2C configuration, transaction execution, and response formatting.


#################################
Static structure
#################################

Files:
* serialToI2CApp.h
* serialToI2CAppCfg.h
* serialToI2CAppUnit.c

..  uml::

	@startuml
	class SerialToI2C_Context
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
	participant SerialToI2C
	participant I2C
	Host -> SerialToI2C : Command
	SerialToI2C -> I2C : Write/Read
	SerialToI2C --> Host : Response
	@enduml


#################################
What is this component about?
#################################

The Serial-to-I2C App translates serial commands to I2C transactions.


#################################
Static structure
#################################

..  uml:: serialToI2CAppStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: serialToI2CAppStateMachine.puml

* Sequence diagram
..  uml:: serialToI2CAppSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide serial-controlled I2C transactions.

Assumptions and influencing factors:
************************************
* I2C master driver is available.

Solutions list:
***************
Solution 1 - Direct I2C operations
Map commands to I2C transfers.

Solution 2 - Transaction queue
Queue requests for scheduled execution.

Solution evaluation:
********************
Direct operations are simplest for low traffic.

Final solution:
****************
Solution 1 selected for simplicity.
