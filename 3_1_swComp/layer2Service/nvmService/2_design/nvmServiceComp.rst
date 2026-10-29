#################################
What is this component about?
#################################

The NVM Service provides key-based storage for configuration data.
It wraps the NVM driver with CRC-protected storage for higher-level modules.


#################################
Static structure
#################################

Files:
* nvmService.h
* nvmServiceCfg.h
* nvmServiceUnit.c

..  uml::

	@startuml
	class NvmService_Blob
	class NvmIndex
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> ReadWrite : Save/Load
	ReadWrite --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor App
	participant NvmService
	App -> NvmService : Save(key, blob)
	NvmService -> NvmService : Compute CRC
	NvmService --> App : Status
	@enduml


#################################
What is this component about?
#################################

The NVM Service provides higher-level storage for configuration records.


#################################
Static structure
#################################

..  uml:: nvmServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: nvmServiceStateMachine.puml

* Sequence diagram
..  uml:: nvmServiceSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide record storage abstraction on top of NVM driver.

Assumptions and influencing factors:
************************************
* NVM driver exposes read/write/erase primitives.

Solutions list:
***************
Solution 1 - Fixed record slots
Store records in fixed addresses.

Solution 2 - Log-structured storage
Append-only storage with garbage collection.

Solution evaluation:
********************
Fixed slots are simpler and sufficient for low write counts.

Final solution:
****************
Solution 1 selected for simplicity.
