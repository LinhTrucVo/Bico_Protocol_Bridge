Chapter 6. Runtime View
#######################
This show how the components from chapter 5 cooperate at runtime.
Each scenario has its own puml file and one ``sw_arch`` item, id ``SWARCH_RT_<SCENARIO>``,
linked with ``:realizes:`` to the ``SWREQ_`` requirements it fulfils.
The detailed design of each component links to these items with ``:refines:``,
so the component behaviour follows the scenario.
The scenario could be different for each specific project, what represented here is just an example.

Use the notation that fits the scenario:

- Sequence diagram (primary): component interactions and message exchanges.
- State machine diagram: state-dependent behaviour.
- Activity diagram or flowchart: processing workflows and decisions.
- Textual steps: straightforward scenarios.

Only interfaces declared in chapter 5.3 are used in the diagrams.
Calls follow the layers: External entity -> ASW -> BSW service -> BSW driver -> HAL.
A layer calls only the layer directly below, the ASW never calls a driver or the HAL.
The transport of external requests is not shown in the use cases.

6.1. Important Use Cases
========================
How components cooperate to execute a feature function.
One scenario per function of a feature from ``1_requirement``.

6.1.1. Feature Name 1 - configure parameters
--------------------------------------------
..  sw_arch:: Runtime - Feature Name 1 - configure parameters
   :id: SWARCH_RT_FEATURENAME1_CONFIGURE
   :realizes: SWREQ_FEATURENAME1_001

   The external entity sends a configure request to the application controller. The application
   controller sets the parameter through the config service, which validates and stores it, and responds.

..  uml:: useCase/useCaseConfigure.puml

6.1.2. Feature Name 1 - perform action
--------------------------------------
..  sw_arch:: Runtime - Feature Name 1 - perform action
   :id: SWARCH_RT_FEATURENAME1_ACTION
   :realizes: SWREQ_FEATURENAME1_002

   The external entity sends a set output command to the application controller. The application
   controller gets the channel configuration from the config service, checks the channel is an output,
   sets it through the IO service and returns the command response.

..  uml:: useCase/useCasePerformAction.puml

6.2. External Interactions
==========================
Communication between the system and external systems, seen at the system boundary.
Internal components are not shown, see 6.1.

..  sw_arch:: Runtime - external interaction
   :id: SWARCH_RT_EXTERNAL
   :realizes: SWREQ_FEATURENAME1_001, SWREQ_FEATURENAME1_002

   Request/response, events sent by the system and handling of invalid requests,
   with the timing the external entity can expect.

..  uml:: externalInteraction/externalInteraction.puml

6.3. Startup and Shutdown
=========================
Initialization and termination sequences, shown as a state machine of the application controller.

..  Replace :realizes: with the SWREQ_ id of the startup / shutdown requirement.

..  sw_arch:: Runtime - startup and shutdown
   :id: SWARCH_RT_STARTUP_SHUTDOWN
   :realizes: SWREQ_FEATURENAME1_001

   At power on, the HAL, drivers, services and applications are initialized in this order.
   ``ApplicationController_start()`` enters the running state, ``ApplicationController_stop()``
   stores the data and stops the components in the reverse order.

..  uml:: startupShutdown/startupShutdown.puml

6.4. Error and Exception Scenarios
==================================
How components react to failures, e.g. communication timeout, invalid data, failed authentication.
One scenario per failure.

6.4.1. Communication timeout
----------------------------
..  sw_arch:: Runtime - communication timeout
   :id: SWARCH_RT_COM_TIMEOUT
   :realizes: SWREQ_FEATURENAME1_002

   The com service checks the driver status after sending. On timeout it retries up to
   ``<max retries>`` times, then reports the error to the application controller,
   which enters the error state.

..  uml:: errorScenario/errorComTimeout.puml

6.5. Runtime Message Exchanges
==============================
Messages exchanged between components at runtime, with their trigger and timing.
Each row is an interface call from a scenario above.

..  sw_arch:: Runtime - message exchanges
   :id: SWARCH_RT_MSG_EXCHANGE
   :realizes: SWREQ_FEATURENAME1_001, SWREQ_FEATURENAME1_002

   Timing and trigger of the interface calls used in 6.1 to 6.4.

..  list-table::
   :header-rows: 1
   :widths: 18 18 30 14 10 10

   * - Sender
     - Receiver
     - Interface
     - Trigger
     - Timing
     - Scenario
   * - Application controller
     - Config service
     - ``ConfigService_setParameter(id, value)``
     - configure request
     - <t> ms
     - 6.1.1
   * - Config service
     - Storage service
     - ``StorageService_writeData(key, data)``
     - value valid
     - <t> ms
     - 6.1.1
   * - Storage service
     - Storage driver
     - ``StorageDriver_flashWrite(address, data)``
     - write data
     - <t> ms
     - 6.1.1
   * - Application controller
     - Config service
     - ``ConfigService_getParameter(id)``
     - set output command
     - <t> ms
     - 6.1.2
   * - Application controller
     - IO service
     - ``IoService_setOutput(channel, level)``
     - channel is output
     - <t> ms
     - 6.1.2
   * - IO service
     - IO driver
     - ``IoDriver_writePin(pin, level)``
     - set output
     - <t> ms
     - 6.1.2
   * - Application controller
     - Com service
     - ``ComService_sendMessage(id, data)``
     - message to send
     - <t> ms
     - 6.4.1
   * - Com service
     - Com driver
     - ``ComDriver_getCanStatus()``
     - after send, cyclic
     - <period> ms
     - 6.4.1
