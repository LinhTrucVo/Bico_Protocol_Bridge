..  c:namespace:: CentralAppController

centralAppControllerUnit.c
###########################

Application layer component providing UDS command dispatching. Parses requests via Deserialize,
maps DID/RID to downstream typed APIs (ConfigService for reads/writes, peripheral apps for
routine control), and builds responses via Serialize.

..  doxygenfile:: centralAppControllerUnit.c
    :project: CentralAppController