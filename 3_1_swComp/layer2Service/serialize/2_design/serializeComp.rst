#################################
What is this component about?
#################################

The Serialize service builds UDS (ISO 14229) response frames including positive responses
for ReadDataByIdentifier (0x62), WriteDataByIdentifier (0x6E), RoutineControl (0x71),
and negative responses (0x7F + NRC). It has no DID/RID semantic knowledge.


#################################
Static structure
#################################

..  uml:: serializeStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: serializeStateMachine.puml

* Sequence diagram
..  uml:: serializeSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide UDS response frame construction for the Central Application Controller.

Assumptions and influencing factors:
************************************
* Response buffer is statically allocated (256 bytes max).
* DID/RID encoded big-endian in response frames.
* Caller provides response data; Serialize only assembles the frame.

Solutions list:
***************
Solution 1 - Builder pattern with dedicated functions
Separate build functions per response type (Read, Write, Routine, Negative).

Solution 2 - Generic frame builder
Single function with parameters for all frame types.

Solution evaluation:
********************
Builder pattern provides type safety and clear semantics per response type.

Final solution:
****************
Solution 1 selected for clarity and compile-time safety.