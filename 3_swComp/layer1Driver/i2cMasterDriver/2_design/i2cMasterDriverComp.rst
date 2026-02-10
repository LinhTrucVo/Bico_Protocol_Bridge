#################################
What is this component about?
#################################

The I2C Master Driver abstracts I2C master transactions and configuration.


#################################
Static structure
#################################

..  uml:: i2cMasterDriverStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: i2cMasterDriverStateMachine.puml

* Sequence diagram
..  uml:: i2cMasterDriverSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide a portable I2C master abstraction layer.

Assumptions and influencing factors:
************************************
* Vendor HAL handles low-level timing.

Solutions list:
***************
Solution 1 - HAL wrapper
Wrap vendor I2C HAL.

Solution 2 - Bit-banging
Implement software I2C for portability.

Solution evaluation:
********************
HAL wrapper offers better performance and timing accuracy.

Final solution:
****************
Solution 1 selected for performance and portability.
