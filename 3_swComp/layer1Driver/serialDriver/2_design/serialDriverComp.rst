#################################
What is this component about?
#################################

The Serial Driver abstracts UART initialization and data transfer operations.


#################################
Static structure
#################################

..  uml:: serialDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: serialDriverStateMachine.puml

* Sequence diagram
..  uml:: serialDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a consistent UART access API independent of hardware.

Assumptions and influencing factors:
************************************
* UART peripheral supports DMA and interrupts if enabled.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor UART HAL.

Solution 2 - Custom UART driver
Implement full UART driver per platform.

Solution evaluation:
********************
HAL wrapper reduces platform-specific code and shortens integration time.

Final solution:
****************
Solution 1 selected for portability.
