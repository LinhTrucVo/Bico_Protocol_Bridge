#################################
What is this component about?
#################################

The Serial-to-Digital Application provides typed GPIO and PWM operations. It is called
by the Central Application Controller via RID 0x02xx (GPIO) and RID 0x03xx (PWM).
This module has no UDS awareness - it receives typed parameters and returns typed results.


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
Design choices
#################################
Description:
************
Provide hardware-abstracted GPIO read/write and PWM start/stop for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* GPIO and PWM drivers are initialized and available.
* Pin/channel numbers are validated at driver level.
* No UDS framing knowledge required in this module.

Solutions list:
***************
Solution 1 - Separate functions per operation
Expose WriteGpio, ReadGpio, StartPwm, StopPwm individually.

Solution 2 - Combined GPIO/PWM function with operation parameter
Single function with operation enum.

Solution evaluation:
********************
Separate functions provide clear API semantics and match 1:1 with RID mapping.

Final solution:
****************
Solution 1 selected for API clarity.