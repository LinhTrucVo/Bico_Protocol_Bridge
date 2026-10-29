#################################
What is this component about?
#################################

The Serial-to-I2C Application provides typed I2C write and read operations. It is called
by the Central Application Controller via RID 0x0400 (I2C Write) and RID 0x0401 (I2C Read).
Receives typed parameters and returns typed results.


#################################
Static structure
#################################

..  uml:: I2cServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: I2cServiceStateMachine.puml

* Sequence diagram
..  uml:: I2cServiceSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide hardware-abstracted I2C master read/write for the CAC dispatcher.

Assumptions and influencing factors:
************************************
* I2C master driver is initialized and available.
* Address is 7-bit, data buffer and length provided by caller.

Solutions list:
***************
Solution 1 - Separate Write/Read functions
Expose Write(addr, pData, len) and Read(addr, pData, len).

Solution 2 - Combined transfer function with direction parameter
Single function with read/write flag.

Solution evaluation:
********************
Separate functions match the RID mapping (0x0401=Write, 0x0402=Read) and are more explicit.

Final solution:
****************
Solution 1 selected for clarity and RID alignment.