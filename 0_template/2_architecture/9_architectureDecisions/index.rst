Chapter 9. Architecture Decisions
#################################
This records the important architecture decisions, one Architecture Decision Record (ADR) per decision.
Each decision has its own number 9.<n> and uses the elements below.
A decision is never deleted, when it changes, set its status to Deprecated or Superseded and add a new decision.
The decisions represented here are just an example, the actual decisions depend on the specific project.

..  list-table::
   :header-rows: 1
   :widths: 20 80

   * - Element
     - Description
   * - Title
     - Short name of the decision
   * - Status
     - Proposed, Accepted, Rejected, Deprecated, Superseded
   * - Context
     - Problem or situation requiring a decision
   * - Decision
     - The selected solution
   * - Alternatives
     - Other considered solutions
   * - Rationale
     - Why the selected solution is preferred
   * - Consequences
     - Benefits, limitations, and trade-offs
   * - References
     - Related requirements, standards, and decisions

Copy this skeleton for a new decision:

..  code-block:: rst

   9.<n>. Decision <n>: <Title>
   ============================
   ..  list-table::
      :widths: 20 80

      * - Status
        - <Proposed | Accepted | Rejected | Deprecated | Superseded by 9.<m>>
      * - Context
        - <problem or situation>
      * - Decision
        - <selected solution>
      * - Alternatives
        - <other solutions considered>
      * - Rationale
        - <why the selected solution is preferred>
      * - Consequences
        - <benefits, limitations, trade-offs>
      * - References
        - <SWREQ_ / SWARCH_ ids, standards, other decisions>

9.1. Decision 1: Use a config service for runtime parameters
============================================================
..  list-table::
   :widths: 20 80

   * - Status
     - Accepted
   * - Context
     - The external entity can change parameters at runtime (feature Name 1, function 1),
       and other functions read them (function 2). Without a common owner, each application
       would read and write the storage service itself, with its own keys and its own value checks.
   * - Decision
     - Add a config service in the BSW service package. Applications set and get parameters only through
       ``ConfigService_setParameter(id, value)`` and ``ConfigService_getParameter(id)``.
       The config service validates each value, stores it through the storage service and keeps a RAM copy.
   * - Alternatives
     - 1. Applications call the storage service directly.
       2. Each application keeps its own parameters in RAM only.
   * - Rationale
     - One place validates and stores the parameters, so the rules are not duplicated.
       Reading from the RAM copy is fast and does not access the flash for each command.
       Alternative 1 spreads the storage keys and checks over all applications.
       Alternative 2 loses the parameters at power off.
   * - Consequences
     - Benefit: applications do not depend on the storage layout, a new parameter is added in one component.
       Limitation: one more component to design and test.
       Trade-off: the RAM copy uses memory for every parameter.
   * - References
     - :need:`SWREQ_FEATURENAME1_001`, :need:`SWREQ_FEATURENAME1_002`, :need:`SWARCH_CFG_SRV`,
       :need:`SWARCH_RT_FEATURENAME1_CONFIGURE`, chapter 8.7 Configuration Management
