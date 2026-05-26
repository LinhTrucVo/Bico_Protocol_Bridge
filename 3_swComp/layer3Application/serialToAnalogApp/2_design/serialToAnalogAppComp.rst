#################################
What is this component about?
#################################

The Serial-to-Analog Application provides typed ADC read operations. It is called by the
Central Application Controller via RID 0x01xx (RoutineControl). This module has no UDS
awareness - it receives typed parameters and returns typed results.


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
Design choices
#################################
Description:
************
Provide a hardware-abstracted ADC reading interface for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* ADC driver is initialized and available.
* Channel number and raw value are the only parameters needed.
* No UDS framing knowledge required in this module.

Solutions list:
***************
Solution 1 - Single ReadAdc function
Expose a simple ReadAdc(channel, pRawValue) API.

Solution 2 - Buffered multi-sample API
Expose a function that reads multiple samples and returns average.

Solution evaluation:
********************
Single-read is sufficient for current RID mapping; averaging can be added later if needed.

Final solution:
****************
Solution 1 selected for simplicity.