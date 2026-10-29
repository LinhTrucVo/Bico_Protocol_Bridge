#################################
What is this component about?
#################################

The Deserialize service parses UDS (ISO 14229) request frames extracting Service Identifier,
Data Identifier or Routine Identifier, and payload data. It has no DID/RID semantic knowledge.


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
Design choices
#################################
Description:
************
Provide UDS frame structural parsing for request dispatching.

Assumptions and influencing factors:
************************************
* Frames arrive as complete byte buffers (no streaming).
* SID is always byte[0]; DID/RID are always big-endian 2-byte fields.
* Only SID 0x22, 0x2E, and 0x31 are supported.

Solutions list:
***************
Solution 1 - Switch-based SID parser
Parse based on SID value with per-SID length rules.

Solution 2 - Table-driven parser
Use a lookup table mapping SID to parsing function.

Solution evaluation:
********************
Switch-based is simpler with only 3 SIDs and minimal overhead.

Final solution:
****************
Solution 1 selected for clarity and minimal code complexity.