#################################
What is this component about?
#################################

The I2C Slave Driver abstracts I2C slave operation and buffered transfers.


#################################
Static structure
#################################

..  uml:: i2cSlaveDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: i2cSlaveDriverStateMachine.puml

* Sequence diagram
..  uml:: i2cSlaveDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable I2C slave abstraction with buffered transfers.

Assumptions and influencing factors:
************************************
* Vendor HAL provides slave address matching and callbacks.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor I2C slave HAL.

Solution 2 - Minimal ISR implementation
Implement full ISR logic per platform.

Solution evaluation:
********************
HAL wrapper reduces platform-specific ISR complexity.

Final solution:
****************
Solution 1 selected for portability.
