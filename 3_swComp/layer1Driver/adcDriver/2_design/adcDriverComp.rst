#################################
What is this component about?
#################################

The ADC Driver abstracts ADC configuration and sampling operations.


#################################
Static structure
#################################

..  uml:: adcDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: adcDriverStateMachine.puml

* Sequence diagram
..  uml:: adcDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a thin HAL wrapper for ADC access and configuration.

Assumptions and influencing factors:
************************************
* Vendor HAL is used for register access.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor HAL APIs.

Solution 2 - Direct register access
Implement register operations per platform.

Solution evaluation:
********************
HAL wrapper improves portability and reduces platform-specific code.

Final solution:
****************
Solution 1 selected for portability.
