#################################
What is this component about?
#################################

The Serialize Service builds protocol response, event, and error frames from structured data.
It encapsulates header construction, payload packing, and CRC generation for downstream transport.


#################################
Static structure
#################################

Files:
* serialize.h
* serializeCfg.h
* serializeUnit.c

..  uml::

	@startuml
	package serialize {
	  class Serialize_Context
	  class Serialize_Message
	  class Serialize_Buffer
	}
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Building : BuildFrame
	Building --> Idle : Done
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor Caller
	participant Serialize
	Caller -> Serialize : Serialize_BuildFrame()
	Serialize -> Serialize : Compute CRC
	Serialize --> Caller : Frame
	@enduml


#################################
What is this component about?
#################################

The Serialize service builds outgoing protocol frames from responses.


#################################
Static structure
#################################

..  uml:: serializeStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: serializeStateMachine.puml

* Sequence diagram
..  uml:: serializeSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide frame construction utilities for protocol responses.

Assumptions and influencing factors:
************************************
* CRC polynomial matches Deserialize service.

Solutions list:
***************
Solution 1 - Streaming builder
Build frame sequentially with CRC update.

Solution 2 - Buffer then CRC
Compute CRC after buffer build.

Solution evaluation:
********************
Streaming builder is memory efficient.

Final solution:
****************
Solution 1 selected for efficiency.
