Chapter 8. Crosscutting Concepts
################################
This show the rules and principles that apply to all components of chapter 5,
so each component does not define them again.
The detailed design of each component follows these concepts.
The concepts and examples represented here are just an example, the actual concepts depend on the specific project.
If a concept realizes a requirement, wrap it in a ``sw_arch`` item, id ``SWARCH_CC_<CONCEPT>``, with ``:realizes:`` to the ``SWREQ_`` ids.

..  list-table::
   :header-rows: 1
   :widths: 10 30 30

   * - Section
     - Crosscutting concept
     - What to document
   * - 8.1
     - Security
     - Security principles and mechanisms
   * - 8.2
     - Error handling
     - Common error-handling strategy
   * - 8.3
     - Logging and tracing
     - Common logging and diagnostic mechanisms
   * - 8.4
     - Communication
     - Common communication principles
   * - 8.5
     - Memory management
     - Common memory usage rules
   * - 8.6
     - Concurrency
     - Rules for parallel execution
   * - 8.7
     - Configuration management
     - How software behavior is configured
   * - 8.8
     - Watchdog management
     - Common monitoring and recovery strategy
   * - 8.9
     - Initialization
     - Common startup principles

8.1. Security
=============
Security principles and mechanisms: which data is protected, how it is protected and who checks it.

Example:

- Every external command is checked by the application controller before it is executed
  (length, range, allowed channel), invalid commands get a negative response.
- Commands that change the configuration are verified with ``CryptoService_verify(data, signature)``.
- Keys are stored only through the storage service and are never sent to the external entity.
- Debug interfaces are disabled in the release build.

8.2. Error Handling
===================
Common error-handling strategy: how errors are detected, reported, and which reaction each error class has.

Example:

- Every interface returns a status ``BPB_E_OK``, ``BPB_E_NOT_OK``, ``BPB_E_BUSY`` or ``BPB_E_TIMEOUT``,
  the caller always checks it.
- An error is handled in the layer that can react to it, otherwise it is returned to the layer above.
- Errors are reported once with ``DiagnosticService_reportEvent(id)``, by the layer that detects them.

..  list-table::
   :header-rows: 1
   :widths: 20 40 40

   * - Error class
     - Example
     - Reaction
   * - Invalid input
     - parameter out of range
     - reject, negative response, no state change
   * - Transient
     - communication timeout
     - retry up to ``<max retries>`` times (see 6.4.1)
   * - Persistent
     - storage write failed
     - report event, keep the last valid value
   * - Fatal
     - initialization failed
     - enter the error state, outputs in safe state (see 6.3)

8.3. Logging and Tracing
========================
Common logging and diagnostic mechanisms: what is recorded, where it is stored and how it is read out.

Example:

- Diagnostic events are recorded with ``DiagnosticService_reportEvent(id)`` and stored through the storage service.
- The status is read with ``DiagnosticService_getDiagnosticStatus()``.
- Event ids are defined in one configuration file, prefix ``BPB_DIAG_``.
- Trace output is only enabled in the debug build and has no effect on timing in the release build.

8.4. Communication
==================
Common communication principles: message format, addressing, request/response rules and timing.

Example:

- External entities talk only to the ASW, the transport goes through the com service, com driver and HAL.
- Each request gets exactly one response, positive or negative, within ``<t>`` ms.
- Messages are sent with ``ComService_sendMessage(id, data)`` and received with ``ComService_receiveCallBack()``.
- Multi-byte values are sent in ``<little / big>`` endian.

8.5. Memory Management
======================
Common memory usage rules: allocation, buffers and non-volatile data.

Example:

- No dynamic memory allocation after initialization, all buffers are allocated statically.
- Buffer sizes are configured in ``4_config/<comp>Cfg.h``.
- Non-volatile data is accessed only through the storage service, never through the storage driver directly.
- Each component owns its data, other components access it only through its interface.

8.6. Concurrency
================
Rules for parallel execution: tasks, interrupts and protection of shared data.

Example:

- Interrupts only copy data and set a flag, the processing is done in the cyclic task.
- Data shared between an interrupt and a task is protected by a critical section.
- Interfaces that may be called from more than one context are marked reentrant in chapter 5.3.
- Each component lists its cyclic function and the task it runs in.

8.7. Configuration Management
=============================
How software behavior is configured: build time configuration, runtime parameters and their defaults.

Example:

- Build time configuration is in ``4_config/<comp>Cfg.h``, macros start with ``BPB_``.
- Runtime parameters are set and read only through the config service,
  ``ConfigService_setParameter(id, value)`` and ``ConfigService_getParameter(id)``.
- The config service validates each value, stores it through the storage service and keeps a RAM copy.
- At startup the config service loads the parameters, if a value is invalid it uses the default value.

8.8. Watchdog Management
========================
Common monitoring and recovery strategy: what is monitored, who triggers the watchdog and the recovery reaction.

Example:

- The watchdog is triggered only in the cyclic task of the application controller, never from an interrupt.
- It is triggered only if all monitored components reported alive in the last cycle.
- Timeout ``<t>`` ms, the reaction is a reset, the reset reason is reported with ``DiagnosticService_reportEvent(id)``.
- The watchdog is disabled only in the debug build.

8.9. Initialization
===================
Common startup principles: initialization order, dependencies and the state of outputs during startup.

Example:

- Components are initialized bottom-up: HAL, drivers, services, applications (see 6.3).
- Each component has an ``<Comp>_init()`` function, it uses only components already initialized.
- Outputs stay in the safe state until ``ApplicationController_start()``.
- Shutdown runs in the reverse order and stores the data before the drivers are stopped.
