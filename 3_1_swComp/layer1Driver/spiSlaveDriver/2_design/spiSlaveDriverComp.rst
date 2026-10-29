#################################
What is this component about?
#################################

The SPI Slave Driver abstracts SPI slave configuration and buffered transfers.


#################################
Static structure
#################################

..  uml:: spiSlaveDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: spiSlaveDriverStateMachine.puml

* Sequence diagram
..  uml:: spiSlaveDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable SPI slave abstraction with buffered transfers.

Assumptions and influencing factors:
************************************
* Vendor HAL provides SPI slave callbacks.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor SPI slave HAL.

Solution 2 - Custom ISR logic
Implement slave transfer logic manually.

Solution evaluation:
********************
HAL wrapper reduces ISR complexity and improves portability.

Final solution:
****************
Solution 1 selected for portability.
