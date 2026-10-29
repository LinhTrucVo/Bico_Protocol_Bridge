#################################
What is this component about?
#################################

The Central Application Controller (CAC) is the sole UDS-aware component in the system.
It owns all DID and RID mapping, dispatches requests to downstream modules via typed APIs,
and builds UDS responses. Downstream modules (peripheral apps, ConfigService) have no
UDS protocol knowledge.


#################################
Static structure
#################################

..  uml:: centralAppControllerStaticStructure.puml


#################################
Dynamic behaviour
#################################

* State machine diagram
..  uml:: centralAppControllerStateMachine.puml

* Sequence diagram
..  uml:: centralAppControllerSequenceDiagram.puml


#################################
Design choices
#################################
Description:
************
Provide a single centralized UDS command dispatcher that isolates protocol details
from peripheral application logic.

Assumptions and influencing factors:
************************************
* Only SID 0x22, 0x2E, 0x31 are supported.
* Deserialize/Serialize services handle frame parsing/building.
* Peripheral apps expose typed C APIs (no UDS awareness).
* ConfigService handles DID-mapped configuration parameters.

Solutions list:
***************
Solution 1 - Central dispatcher with DID/RID switch
CAC switches on DID/RID to route to correct downstream module.

Solution 2 - Registration-based routing
Downstream modules register handlers at startup.

Solution evaluation:
********************
Central switch is simpler, fully deterministic, and easier to test with known DID/RID set.

Final solution:
****************
Solution 1 selected for deterministic routing and testability.