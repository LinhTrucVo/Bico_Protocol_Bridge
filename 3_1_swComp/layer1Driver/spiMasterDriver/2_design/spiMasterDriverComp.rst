#################################
What is this component about?
#################################

The SPI Master Driver abstracts SPI master configuration and transfers.


#################################
Static structure
#################################

..  uml:: spiMasterDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: spiMasterDriverStateMachine.puml

* Sequence diagram
..  uml:: spiMasterDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable SPI master abstraction with chip select handling.

Assumptions and influencing factors:
************************************
* Vendor HAL provides SPI transfer operations.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor SPI HAL.

Solution 2 - Bit-banging
Software-driven SPI for maximum portability.

Solution evaluation:
********************
HAL wrapper ensures timing accuracy and performance.

Final solution:
****************
Solution 1 selected for performance and portability.
