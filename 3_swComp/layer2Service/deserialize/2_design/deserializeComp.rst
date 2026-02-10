#################################
What is this component about?
#################################

The Deserialize service parses incoming frames into requests and payloads.


#################################
Static structure
#################################

..  uml:: deserializeStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: deserializeStateMachine.puml

* Sequence diagram
..  uml:: deserializeSequenceDiagram.puml


#################################
Design chooices
#################################
Description:
************
Provide frame parsing and validation for protocol requests.

Assumptions and influencing factors:
************************************
* CRC polynomial matches Serialize service.

Solutions list:
***************
Solution 1 - Streaming parser
Parse bytes incrementally.

Solution 2 - Full buffer parser
Parse only once buffer is complete.

Solution evaluation:
********************
Streaming parser allows early validation and lower latency.

Final solution:
****************
Solution 1 selected for responsiveness.
Centralized parser provides consistent validation and reduces duplicated code.

Final solution:
****************
Solution 1 selected for consistent validation and command extraction.
