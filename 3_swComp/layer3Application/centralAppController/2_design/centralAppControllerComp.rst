#################################
What is this component about?
#################################

The Central App Controller coordinates command parsing, dispatch, and response generation.
It routes validated requests to application modules and returns serialized responses.


#################################
Static structure
#################################

Files:
* centralAppController.h
* centralAppControllerCfg.h
* centralAppControllerUnit.c

..  uml::

	@startuml
	class CentralAppController_Context
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Processing : ProcessFrame
	Processing --> Dispatching : Validated
	Dispatching --> Idle : ResponseReady
	Processing --> Error : Invalid
	Error --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor Host
	participant Central
	participant Deserialize
	participant App
	participant Serialize
	Host -> Central : Frame
	Central -> Deserialize : ParseFrame
	Central -> App : Dispatch
	Central -> Serialize : BuildFrame
	Central --> Host : Response
	@enduml


#################################
What is this component about?
#################################

The Central App Controller orchestrates request parsing and dispatch.


#################################
Static structure
#################################

..  uml:: centralAppControllerStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: centralAppControllerStateMachine.puml

* Sequence diagram
..  uml:: centralAppControllerSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a single entry point for request routing and processing.

Assumptions and influencing factors:
************************************
* Serialize/Deserialize services are available.

Solutions list:
***************
Solution 1 - Central dispatcher
Controller routes to application handlers.

Solution 2 - Distributed routing
Each application module handles parsing.

Solution evaluation:
********************
Central dispatcher simplifies integration and testing.

Final solution:
****************
Solution 1 selected for maintainability.
