#################################
What is this component about?
#################################

The Calibration Service manages per-channel gain and offset data and applies calibration to measurements.
It supports two-point calibration and persistence to non-volatile memory.


#################################
Static structure
#################################

Files:
* calibrationService.h
* calibrationServiceCfg.h
* calibrationServiceUnit.c

..  uml::

	@startuml
	class Calibration_Data {
	  +offset
	  +gain
	  +valid
	}
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Applying : Apply
	Applying --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor App
	participant Calibration
	App -> Calibration : Apply(channel, value)
	Calibration --> App : calibrated value
	@enduml


#################################
What is this component about?
#################################

The Calibration Service applies calibration profiles to raw signals.


#################################
Static structure
#################################

..  uml:: calibrationServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: calibrationServiceStateMachine.puml

* Sequence diagram
..  uml:: calibrationServiceSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide configurable calibration (offset/gain) per channel.

Assumptions and influencing factors:
************************************
* Calibration parameters are stored by Config/NVM services.

Solutions list:
***************
Solution 1 - Linear calibration
Offset + gain applied per channel.

Solution 2 - Lookup table
Use piecewise calibration tables.

Solution evaluation:
********************
Linear calibration is simpler and sufficient for typical sensors.

Final solution:
****************
Solution 1 selected for simplicity.
