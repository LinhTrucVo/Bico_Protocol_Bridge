..  c:namespace:: Deserialize

deserializeUnit.c
###########################

Service layer component providing UDS request frame parsing. Extracts Service Identifier (SID),
Data Identifier (DID) or Routine Identifier (RID), routine control type, and payload data
from raw byte buffers for dispatch by the Central Application Controller.

..  doxygenfile:: deserializeUnit.c
    :project: Deserialize