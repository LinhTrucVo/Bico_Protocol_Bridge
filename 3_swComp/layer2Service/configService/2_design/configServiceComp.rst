#################################
What is this component about?
#################################

The Config Service stores and validates configuration for analog, digital, PWM, I2C, SPI, and serial settings.
It provides centralized validation and access APIs for other modules.


#################################
Static structure
#################################

Files:
* configService.h
* configServiceCfg.h
* configServiceUnit.c

..  uml::

	@startuml
	class ConfigStore
	ConfigStore : serial
	ConfigStore : analog
	ConfigStore : digital
	ConfigStore : pwm
	ConfigStore : i2c
	ConfigStore : spi
	@enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

	@startuml
	[*] --> Idle
	Idle --> Validating : SetConfig
	Validating --> Idle : Valid
	Validating --> Error : Invalid
	Error --> Idle
	@enduml

* Sequence diagram
..  uml::

	@startuml
	actor App
	participant Config
	App -> Config : SetAnalogChannelConfig()
	Config -> Config : Validate
	Config --> App : Status
	@enduml


#################################
What is this component about?
#################################

The Config Service manages configuration parameters across components.


#################################
Static structure
#################################

..  uml:: configServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: configServiceStateMachine.puml

* Sequence diagram
..  uml:: configServiceSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide centralized storage and validation for configuration parameters.

Assumptions and influencing factors:
************************************
* NVM is used for persistence when enabled.

Solutions list:
***************
Solution 1 - Key/value storage
Simple key/value with validation rules.

Solution 2 - Structured config blobs
Store binary configuration structs per module.

Solution evaluation:
********************
Key/value storage provides flexibility with small memory impact.

Final solution:
****************
Solution 1 selected for flexibility.
