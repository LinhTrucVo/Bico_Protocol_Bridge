#################################
What is this component about?
#################################

The Data Conversion Service converts ADC raw samples into engineering units based on per-channel settings.
It supports voltage, millivolt, and percentage conversions.

#################################
Static structure
#################################

Files:
* dataConversionService.h
* dataConversionServiceCfg.h
* dataConversionServiceUnit.c

..  uml::

	@startuml
	class Conversion_Config {
	  +resolutionBits
	  +vRef
	  +scale
	  +offset
	  +unit
	}
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Converting : Convert
	Converting --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor App
	participant Conversion
	App -> Conversion : Convert(channel, raw)
	Conversion --> App : value
	@enduml


#################################
What is this component about?
#################################

The Data Conversion Service converts between raw and engineering units.


#################################
Static structure
#################################

..  uml:: dataConversionServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: dataConversionServiceStateMachine.puml

* Sequence diagram
..  uml:: dataConversionServiceSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide conversion utilities for raw and engineering units.

Assumptions and influencing factors:
************************************
* Channel-specific scaling is configured externally.

Solutions list:
***************
Solution 1 - Linear conversion
Scale and offset conversion.

Solution 2 - Polynomial conversion
Higher order conversion for accuracy.

Solution evaluation:
********************
Linear conversion is sufficient for most use cases.

Final solution:
****************
Solution 1 selected for simplicity.
