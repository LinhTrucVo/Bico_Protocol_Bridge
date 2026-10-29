#################################
What is this component about?
#################################

The NVM Driver abstracts non-volatile memory read, write, and erase operations.


#################################
Static structure
#################################

..  uml:: nvmDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: nvmDriverStateMachine.puml

* Sequence diagram
..  uml:: nvmDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable NVM abstraction with basic integrity support.

Assumptions and influencing factors:
************************************
* Vendor HAL provides flash/EEPROM operations.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor NVM HAL.

Solution 2 - External storage driver
Implement separate driver per memory type.

Solution evaluation:
********************
HAL wrapper keeps portability and simplifies integration.

Final solution:
****************
Solution 1 selected for portability.
