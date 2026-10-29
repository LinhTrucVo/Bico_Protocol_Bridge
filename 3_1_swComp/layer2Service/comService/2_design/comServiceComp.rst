#################################
What is this component about?
#################################

The ComService provides a buffered communication abstraction over the Serial Driver.
It manages Rx and Tx ring-buffers allowing upper layers to read and write frames without
direct interaction with the Serial Driver hardware interface.


#################################
Static structure
#################################

..  uml:: comServiceStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: comServiceStateMachine.puml

* Sequence diagram
..  uml:: comServiceSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide buffered serial communication with ring-buffer management.

Assumptions and influencing factors:
************************************
* Serial Driver provides polling-based Rx data retrieval.
* Frames are bounded by a maximum size (configurable).
* Upper layers call Run periodically to transfer data.

Solutions list:
***************
Solution 1 - Ring-buffer with head/tail indices
Classic ring-buffer using modular arithmetic on fixed-size arrays.

Solution 2 - Linked list of dynamic buffers
Dynamically allocated frame buffers linked in a queue.

Solution evaluation:
********************
Ring-buffer is deterministic, uses no dynamic allocation, and is suitable for embedded systems.
