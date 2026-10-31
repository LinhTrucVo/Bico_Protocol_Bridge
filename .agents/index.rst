Agent Workflow
##############

.. What is this document:
.. How a ticket is processed by the AI agent team, from the change request to the integrated software.

A ticket is processed by five custom agents defined in ``.github/agents/``. Each agent follows the
project rules in ``AGENTS.md`` and the step instructions in ``.agents/instruction/``.
Agents work only above the HAL and never read or write a hardware workspace (``7_x_*``).

Acronyms and terms
******************

.. list-table::
   :header-rows: 1
   :widths: 20 80

   * - Term
     - Meaning
   * - ASPICE
     - Automotive SPICE (Software Process Improvement and Capability dEtermination), version 4.0. Process standard followed by this project.
   * - SWE.1 ... SWE.6
     - ASPICE software engineering process steps: SWE.1 Software Requirements Analysis, SWE.2 Software Architectural Design,
       SWE.3 Software Detailed Design and Unit Construction, SWE.4 Software Unit Verification,
       SWE.5 Software Component Verification and Integration Verification, SWE.6 Software Verification (qualification test).
   * - G1 ... G5
     - Gates: checkpoints between workflow phases. Work continues only when the gate check passes. See `Gates`_.
   * - HAL
     - Hardware Abstraction Layer. Here: the port API ``<Drv>Port_*`` that each layer1 driver declares in ``3_inc/<drv>Porting.h``
       and each hardware workspace implements.
   * - HIL
     - Hardware In the Loop. Test set-up with real hardware, needed for SWE.6 (not available yet).
   * - MISRA C:2012
     - Coding guidelines of the Motor Industry Software Reliability Association for safe C code. Followed by CODER.
   * - BPB
     - Bico Protocol Bridge. Prefix ``BPB_`` of every macro and enum value.
   * - Need, need ID
     - Traceable item of Sphinx-Needs (``sw_req``, ``sw_arch``, ...) with a unique ID (``SWREQ_...``). See `Traceability`_.
   * - Shared file
     - File edited by more than one step: ``3_1_swComp/bicoProtocolBridgeSwComp.cmake``,
       ``5_buildEnviroment/unitTestBuild/CMakeLists.txt`` and the toctree ``index.rst`` files.
   * - Interface freeze
     - After G3, ``3_inc`` and ``4_config`` of a component do not change, so code, unit tests and integration tests can be
       written in parallel.
   * - fff
     - Fake Function Framework, used to fake the API of other components in unit tests.
   * - CI
     - Continuous Integration, ``.github/workflows/ci.yml``.
   * - WSL
     - Windows Subsystem for Linux, used to run the build scripts on Windows.

Agent team
**********

.. Who does what, who reviews whom

..  uml:: agentTeam.puml

.. list-table::
   :header-rows: 1
   :widths: 14 22 34 30

   * - Agent
     - SWE steps
     - Writes
     - Reviews
   * - LEADER
     - Coordination
     - Nothing (delegates every change). Local git commits per gate.
     - Build results (G5)
   * - ARCHITECT
     - SWE.1, SWE.2
     - ``1_requirement/``, ``2_architecture/``
     - Design (G3), code (G4) against the architecture
   * - DESIGNER
     - SWE.3 design, SWE.4
     - ``<comp>/1_swcReq``, ``2_design``, ``3_inc``, ``4_config``, ``6_test``
     - Requirements and architecture feasibility (G2)
   * - CODER
     - SWE.3 code
     - ``<comp>/5_src`` (MISRA C:2012)
     - \-
   * - INTEGRATOR
     - SWE.5, builds
     - ``4_1_integrationTest/``
     - \- (reports build results to LEADER)

SWE.6 is blocked until a HIL environment exists.

Gates
*****

.. What is checked between the phases, by whom, and what is committed

..  uml:: workflowGates.puml

.. list-table::
   :header-rows: 1
   :widths: 8 18 16 40 18

   * - Gate
     - Name
     - Checked by
     - Pass criteria
     - Commit
   * - G1
     - Requirements approved
     - User
     - Every point of the ticket Expected Result is covered by a ``sw_req``; requirements are verifiable and hardware independent.
     - ``G1 <id>: requirements``
   * - G2
     - Architecture feasible
     - DESIGNER
     - Requirements are implementable above the HAL, not contradictory, concrete; every ``sw_req`` is realized by an ``sw_arch``.
       After 2 rounds without agreement, LEADER asks the user.
     - ``G2 <id>: architecture``
   * - G3
     - Interfaces frozen
     - ARCHITECT
     - Design follows the architecture and the layer rule; every ``sw_arch`` is refined by an ``sw_detail``;
       ``3_inc`` and ``4_config`` are final. A changed ``*Porting.h`` is reported to the user (no stop).
     - ``G3 <id>: interfaces frozen``
   * - G4
     - Units verified
     - ARCHITECT, INTEGRATOR
     - Code follows design and architecture; all unit tests pass; line and branch coverage >= 90 %.
     - ``G4 <id>: units verified``
   * - G5
     - Integrated
     - LEADER
     - Integration tests pass; full ``docGen.sh`` and ``unitTestBuild.sh`` pass; no new Sphinx-Needs warnings.
     - ``G5 <id>: integrated``

After G3 three tasks run in parallel per component: CODER writes ``5_src``, DESIGNER writes the unit tests
from the design (without reading ``5_src``), INTEGRATOR writes the integration scenarios.
When a gate fails, LEADER assigns the fix: code differs from design -> CODER, test or design is wrong -> DESIGNER
(a design change repeats G3 for that component).

Delegated task
**************

.. How LEADER hands a task to an agent and gets the result back

..  uml:: taskSequence.puml

Every task from LEADER contains:

.. code-block:: text

   Role: <AGENT>    Step: <SWE.x / review Gx>    Ticket: <id>
   Follow: .agents/instruction/<step>/instructions.md and AGENTS.md
   Component(s): <list or "all">
   Input base: <commit>   (git diff <commit> -- <folder>)
   You may write: <folders>
   Shared files granted: <list or "none">
   Do not: write outside the folders above, edit 7_x_*, change frozen 3_inc headers (after G3)
   Return: the report format of your agent file

Rules:

- **Change detection:** each step finds its input changes with ``git diff <previous gate commit> -- <input folder>``.
- **Shared files:** LEADER grants a shared file to one running agent only. An agent that needs another shared file returns a request.
- **Interface change after G3:** CODER or the test writer stops and returns a request. LEADER sends DESIGNER a design fix and repeats G3.
- **Builds:** INTEGRATOR runs the scripts from the repository root, with ``bash <script>`` on Linux and ``wsl bash <script>`` on Windows.

Traceability
************

.. Sphinx-Needs types and links defined in 5_buildEnviroment/docGen/aspice_config.py

..  uml:: sweTraceability.puml

.. list-table::
   :header-rows: 1
   :widths: 10 24 14 26 26

   * - Step
     - Need type
     - ID prefix
     - Link
     - Instruction
   * - SWE.1
     - ``sw_req``
     - ``SWREQ_``
     - \-
     - ``1_requirement_analyzer/instructions.md``
   * - SWE.2
     - ``sw_arch``
     - ``SWARCH_``
     - ``realizes`` -> ``sw_req``
     - ``2_architecture_design/instructions.md``
   * - SWE.3
     - ``sw_detail``, ``sw_unit``
     - ``SWDD_``, ``SWUNIT_``
     - ``refines`` -> ``sw_arch``, ``implements`` -> ``sw_detail``
     - ``3_detailed_design_unit_construction/instructions.md``
   * - SWE.4
     - ``sw_unit_test``
     - ``SWUT_``
     - ``verifies`` -> ``sw_unit``
     - ``4_unit_verification/instructions.md``
   * - SWE.5
     - ``sw_integration_test``
     - ``SWIT_``
     - ``verifies`` -> ``sw_arch``
     - ``5_integration_test/instructions.md``
   * - SWE.6
     - ``sw_qualification_test``
     - ``SWQT_``
     - ``verifies`` -> ``sw_req``
     - ``6_qualification_test/instructions.md`` (blocked)

How to start
************

#. Write the ticket ``0_ticket/<yymmdd>_<hhmmss>.rst`` using ``0_ticket/ticket_template.rst``.
#. In VS Code Chat, select the agent **LEADER** in the agent picker.
#. Type, for example, ``Process ticket 0_ticket/261031_101500.rst``.
#. Approve the requirements when LEADER asks (G1) and answer open questions.
#. At the end, LEADER reports the result and asks whether to delete the ticket.
