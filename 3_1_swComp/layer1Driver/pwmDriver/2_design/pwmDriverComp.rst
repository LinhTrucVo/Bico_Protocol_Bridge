#################################
What is this component about?
#################################

The PWM Driver abstracts PWM channel configuration and control.


#################################
Static structure
#################################

..  uml:: pwmDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: pwmDriverStateMachine.puml

* Sequence diagram
..  uml:: pwmDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable PWM abstraction for timer-based outputs.

Assumptions and influencing factors:
************************************
* Vendor HAL provides timer/PWM setup.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor PWM HAL.

Solution 2 - Direct timer configuration
Implement timer configuration per platform.

Solution evaluation:
********************
HAL wrapper provides portability with minimal effort.

Final solution:
****************
Solution 1 selected for portability.
