#################################
What is this component about?
#################################

The SerialToAnalog App implements the Serial-to-Analog feature for multi-channel ADC operation.
It manages configuration, sampling control, and threshold monitoring using raw ADC values.


#################################
Static structure
#################################

Files:
* serialToAnalogApp.h
* serialToAnalogAppCfg.h
* serialToAnalogAppUnit.c

..  uml::

    @startuml
    class SerialToAnalog_Context
    class SerialToAnalog_ChannelConfig
    @enduml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml::

    @startuml
    [*] --> IDLE
    IDLE --> CONFIGURING : ConfigCommand
    CONFIGURING --> IDLE : ConfigOK
    CONFIGURING --> ERROR : ConfigInvalid
    IDLE --> SAMPLING : Trigger
    SAMPLING --> PROCESSING : SamplesReady
    PROCESSING --> TRANSMITTING : DataReady
    TRANSMITTING --> IDLE : Sent
    ERROR --> IDLE : Cleared
    @enduml

* Sequence diagram
..  uml::

    @startuml
    actor Host
    participant SerialToAnalog
    participant ADC
    participant Serialize
    Host -> SerialToAnalog : Command
    SerialToAnalog -> ADC : Start/Read
    SerialToAnalog -> Serialize : BuildFrame(raw_value)
    SerialToAnalog --> Host : Response
    @enduml


#################################
What is this component about?
#################################

The Serial-to-Analog App translates serial commands to DAC outputs.


#################################
Static structure
#################################

..  uml:: serialToAnalogAppStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: serialToAnalogAppStateMachine.puml

* Sequence diagram
..  uml:: serialToAnalogAppSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a serial-controlled analog output application.

Assumptions and influencing factors:
************************************
* DAC/ADC drivers are available.

Solutions list:
***************
Solution 1 - Direct mapping
Map incoming values directly to output.

Solution 2 - Smoothed output
Apply filtering to output updates.

Solution evaluation:
********************
Direct mapping offers deterministic response.

Final solution:
****************
Solution 1 selected for simplicity.
