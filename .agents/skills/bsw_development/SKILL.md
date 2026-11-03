---
name: embedded-basic-software-development
description: Senior-level platform-independent embedded Basic Software (BSW) development skill for designing, implementing, reviewing, integrating, debugging, and testing common embedded software infrastructure in C/C++. Use when working with hardware-independent services, system initialization, lifecycle management, communication services, diagnostics, memory management, watchdogs, power management, scheduling, synchronization, and hardware abstraction.
---

# Senior Embedded Basic Software Development

## 1. Role and Expectations

Act as a Senior Embedded Software Engineer specializing in embedded Basic Software (BSW) architecture and development.

Your responsibility is to design and maintain reusable software infrastructure between hardware-specific drivers and application software.

BSW should provide common services that applications can use without depending directly on MCU registers, peripheral drivers, or hardware-specific implementation details.

Responsibilities:

- Design reusable and hardware-independent software services.
- Define clear interfaces between application, service, and hardware layers.
- Manage system initialization and lifecycle.
- Develop communication and data-management services.
- Implement diagnostics and error reporting.
- Implement scheduling, synchronization, and event management.
- Integrate hardware drivers and operating systems.
- Manage persistent data and system configuration.
- Implement watchdog and system health monitoring.
- Manage power states and low-power transitions.
- Ensure deterministic behavior and resource efficiency.
- Define testable requirements and verification strategies.

Prioritize modularity, portability, reliability, determinism, maintainability, and testability.

## 2. BSW Architecture and Responsibilities

BSW is the infrastructure layer responsible for providing common embedded software functionality.

A typical architecture:

```text
Application Layer
    |
    | Application APIs
    |
Basic Software (BSW)
    |
    +-- System Services
    +-- Communication Services
    +-- Memory Services
    +-- Diagnostic Services
    +-- Power Management Services
    +-- Watchdog / Health Monitoring
    +-- Scheduling / Synchronization
    +-- Configuration Services
    |
Hardware Abstraction Layer (HAL)
    |
Hardware Drivers
    |
MCU / External Hardware
```

The exact architecture depends on the project. Some systems integrate the OS or hardware abstraction layer within the broader BSW structure.

### BSW design principles

1. Application software must not depend unnecessarily on hardware-specific implementation details.
2. Hardware-dependent operations must be isolated behind appropriate interfaces.
3. Common services should be reusable across MCU platforms.
4. Service responsibilities must be clearly separated.
5. Dependencies between services must be explicit.
6. Initialization and shutdown order must be deterministic.
7. Every service must define error behavior and resource ownership.
8. Interfaces must be designed for testability.

Do not create a BSW layer simply to wrap every hardware API. Each service must provide meaningful abstraction, coordination, or reusable functionality.

## 3. Common BSW Service Categories

Understand the responsibilities and typical interfaces of common embedded services.

### 3.1 System Initialization and Lifecycle Management

Responsibilities:

- System startup.
- Initialization sequencing.
- System state management.
- Shutdown coordination.
- Reset handling.
- Startup diagnostics.
- Runtime lifecycle management.

Typical interfaces:

```c
void Bsw_Init(void);
void Bsw_Start(void);
void Bsw_Shutdown(void);
void Bsw_MainFunction(void);
```

These are illustrative APIs. Define interfaces according to project architecture.

Consider:

- Cold boot and warm boot.
- Bootloader-to-application handover.
- Initialization dependencies.
- Partial initialization failure.
- Startup timeout.
- Shutdown requests.
- Reset reasons.
- Recovery behavior.

Do not initialize modules in arbitrary order. Model dependencies explicitly.

### 3.2 Communication Services

Responsibilities:

- Provide common communication interfaces.
- Manage communication channels.
- Handle asynchronous data transfer.
- Manage communication buffers.
- Provide message framing and parsing where appropriate.
- Handle timeouts and communication errors.
- Coordinate communication resources.

Examples:

- UART communication service.
- SPI device communication service.
- I2C device communication service.
- CAN communication service.
- Ethernet communication service.
- USB communication service.
- Inter-process communication.

Consider:

- Synchronous and asynchronous APIs.
- Message boundaries.
- Buffer ownership.
- Concurrency.
- Flow control.
- Communication state.
- Timeout and recovery.
- Data integrity.
- Communication diagnostics.

Do not mix physical communication drivers with application-specific protocol logic.

### 3.3 Memory Management Services

Responsibilities:

- Provide common memory access interfaces.
- Manage memory regions.
- Manage persistent data.
- Provide data integrity checks.
- Manage storage allocation where required.
- Provide memory protection and validation.
- Coordinate memory operations.

Examples:

- Memory abstraction.
- Non-volatile memory service.
- Configuration storage.
- Calibration storage.
- Persistent counters.
- Data logging.
- Memory pool management.

Consider:

- RAM versus non-volatile memory.
- Memory alignment.
- Memory ownership.
- Storage endurance.
- Power-failure safety.
- Data versioning.
- CRC and integrity validation.
- Memory boundaries.
- Concurrent access.

Do not treat RAM allocation and persistent storage as the same service.

### 3.4 Diagnostic Services

Responsibilities:

- Collect software and hardware errors.
- Manage diagnostic events.
- Provide error reporting interfaces.
- Maintain error history where required.
- Expose diagnostic information.
- Support fault recovery.
- Provide system health information.

Consider:

- Error classification.
- Error severity.
- Error identifiers.
- Event lifecycle.
- Fault detection and confirmation.
- Error counters.
- Diagnostic snapshots.
- Persistent diagnostic storage.
- Runtime versus development diagnostics.

Distinguish between detecting an error, reporting an error, storing an error, and recovering from an error.

### 3.5 Watchdog and Health Monitoring

Responsibilities:

- Monitor software execution.
- Detect stalled tasks.
- Detect missed deadlines.
- Detect invalid system states.
- Coordinate hardware watchdog servicing.
- Trigger recovery or reset when necessary.

Consider:

- Task supervision.
- Alive monitoring.
- Deadline monitoring.
- Logical execution monitoring.
- Startup supervision.
- Shutdown supervision.
- Watchdog window constraints.
- Fault escalation.
- Recovery policies.

Do not service a watchdog unconditionally from a periodic timer. Servicing should reflect actual system health.

### 3.6 Scheduling and Synchronization Services

Responsibilities:

- Coordinate service execution.
- Manage periodic and event-driven processing.
- Provide synchronization primitives.
- Manage shared resources.
- Coordinate asynchronous operations.

Examples:

- Main function scheduling.
- Task management.
- Event notification.
- Mutex abstraction.
- Semaphore abstraction.
- Critical sections.
- Work queues.
- Timer services.

Consider:

- Bare-metal versus RTOS execution.
- Task priorities.
- ISR/task interaction.
- Execution context.
- Race conditions.
- Deadlocks.
- Priority inversion.
- Timing jitter.
- Reentrancy.
- Bounded execution time.

Do not implement a second scheduler when an existing RTOS already provides the required functionality.

### 3.7 Power Management Services

Responsibilities:

- Manage system power states.
- Coordinate peripheral power states.
- Handle sleep and wake-up.
- Manage clock transitions.
- Coordinate power-dependent services.
- Restore system state after wake-up.

Consider:

- Active mode.
- Idle mode.
- Sleep mode.
- Deep sleep.
- Standby or shutdown.
- Wake-up sources.
- Peripheral dependencies.
- Data retention.
- Clock restoration.
- Pending communication and memory operations.

Do not enter low-power mode while critical operations are still active.

### 3.8 Configuration and Parameter Services

Responsibilities:

- Provide access to system configuration.
- Validate configuration values.
- Manage default values.
- Support runtime parameter updates.
- Manage configuration versions.
- Persist configurable parameters when required.

Consider:

- Compile-time configuration.
- Build-time configuration.
- Runtime configuration.
- Persistent configuration.
- Configuration validation.
- Default restoration.
- Version migration.
- Access permissions.

Separate static hardware configuration from application-adjustable parameters.

### 3.9 Time and Timer Services

Responsibilities:

- Provide system time.
- Provide monotonic time.
- Manage software timers.
- Provide timeout handling.
- Support periodic execution.
- Coordinate timestamps and time synchronization.

Consider:

- Tick resolution.
- Timer accuracy.
- Timer overflow.
- Monotonic versus wall-clock time.
- Clock drift.
- Deadline calculation.
- Tickless operation.
- Time synchronization.

Do not use wall-clock time for elapsed-time calculations when a monotonic clock is available.

### 3.10 Security Services

Responsibilities:

- Provide common security-related functionality.
- Manage access control.
- Support cryptographic services.
- Protect sensitive configuration and data.
- Coordinate secure storage.
- Provide security event reporting.

Examples:

- Cryptographic service abstraction.
- Random number generation.
- Key management interface.
- Secure configuration access.
- Authentication service.
- Secure communication support.

Consider:

- Key lifecycle.
- Secret storage.
- Authentication.
- Authorization.
- Data integrity.
- Confidentiality.
- Replay protection.
- Secure update interaction.
- Fault reporting.

Do not implement cryptographic algorithms from scratch when established and reviewed implementations are available.

## 4. Layering and Dependency Management

Define clear responsibilities between software layers.

Recommended dependency direction:

```text
Application
    |
BSW Services
    |
Hardware Abstraction
    |
Hardware Drivers
    |
Hardware
```

An RTOS or platform runtime may provide services to multiple layers.

### Dependency rules

- Application code should depend on service interfaces rather than hardware implementation.
- BSW services should use lower-layer interfaces through explicit dependencies.
- Hardware drivers should not depend on application-specific business logic.
- Shared infrastructure should not introduce unnecessary circular dependencies.
- Platform-specific implementations should be replaceable.
- Dependencies should be injectable or mockable for testing.

### Example interface separation

```c
typedef struct
{
    int (*read)(uint32_t address, void *buffer, size_t length);
    int (*write)(uint32_t address, const void *buffer, size_t length);
} Bsw_MemoryInterface_t;
```

The service consumes an interface rather than depending directly on a particular Flash driver.

## 5. API and Interface Design

Design APIs around service responsibilities, not hardware register operations.

### API design principles

- Define clear input and output parameters.
- Use explicit status codes.
- Define synchronous or asynchronous behavior.
- Define buffer ownership.
- Define execution context.
- Define thread-safety guarantees.
- Define timeout behavior.
- Define callback behavior.
- Avoid unnecessary global state.
- Avoid exposing implementation details.

Example:

```c
typedef enum
{
    BSW_STATUS_OK = 0,
    BSW_STATUS_INVALID_PARAM,
    BSW_STATUS_NOT_INITIALIZED,
    BSW_STATUS_BUSY,
    BSW_STATUS_TIMEOUT,
    BSW_STATUS_NOT_SUPPORTED,
    BSW_STATUS_NO_RESOURCE,
    BSW_STATUS_HW_ERROR
} Bsw_Status_t;
```

For asynchronous APIs, define:

- Request acceptance.
- Request completion.
- Cancellation.
- Timeout.
- Error notification.
- Buffer lifetime.

Never use a single generic status code for unrelated failure conditions when the application needs to distinguish them.

## 6. State Machines and Lifecycle

Use explicit state machines for services with lifecycle or asynchronous behavior.

Example:

```text
UNINITIALIZED
      |
      v
INITIALIZING
      |
      v
INITIALIZED
      |
      v
RUNNING
      |
      v
STOPPING
      |
      v
STOPPED
```

Possible error transition:

```text
INITIALIZING / RUNNING
          |
          v
        ERROR
          |
          v
      RECOVERY
          |
          +----> INITIALIZED
          |
          +----> FAILED
```

For each state, define:

- Entry conditions.
- Permitted operations.
- Exit conditions.
- State transitions.
- Timeout behavior.
- Error behavior.
- Recovery behavior.

Do not use loosely related Boolean flags as a substitute for a well-defined state machine.

## 7. Initialization and Dependency Handling

Define initialization order based on actual dependencies.

Example:

```text
1. MCU and clock initialization
2. Memory and low-level hardware initialization
3. Hardware drivers
4. OS or scheduler initialization
5. Common BSW services
6. Communication services
7. Diagnostic and monitoring services
8. Application initialization
9. System operational state
```

The actual order depends on the architecture. Some systems initialize the OS before particular drivers or services.

### Engineering rules

- Define initialization dependencies.
- Check initialization return values.
- Handle partial initialization failure.
- Avoid accessing uninitialized services.
- Define retry or recovery behavior.
- Ensure initialization is idempotent where required.
- Define startup time budgets.
- Separate initialization from operational processing.

## 8. Scheduling and Execution Context

Every service must define where its functions execute.

Possible contexts:

- Main loop.
- Periodic task.
- Background task.
- Interrupt service routine.
- Deferred interrupt processing.
- Callback context.
- Dedicated worker task.

For each API, document:

- Whether it is blocking.
- Whether it is reentrant.
- Whether it is thread-safe.
- Whether it can execute in ISR context.
- Maximum execution time.
- Required synchronization.
- Callback execution context.

### Real-time engineering

Evaluate:

- Worst-case execution time.
- Activation period.
- Scheduling jitter.
- Interrupt latency.
- Blocking time.
- Stack usage.
- CPU utilization.

Do not introduce long-running operations into high-priority tasks or interrupt handlers.

## 9. Buffer and Resource Management

Define ownership for every shared resource.

Consider:

- Static allocation.
- Dynamic allocation.
- Memory pools.
- Ring buffers.
- Message queues.
- DMA buffers.
- Shared communication buffers.
- Persistent storage buffers.

### Engineering rules

- Prefer static allocation in deterministic embedded paths where practical.
- Define buffer capacity and overflow behavior.
- Validate all lengths.
- Avoid buffer overflows and out-of-bounds access.
- Define ownership transfer.
- Avoid use-after-free.
- Avoid data races.
- Consider alignment and DMA accessibility.
- Define resource exhaustion behavior.

Do not assume that `volatile` provides thread safety.

## 10. Error Handling and Fault Management

Use a consistent error-handling strategy across services.

Classify errors:

**Configuration errors**
- Invalid parameters.
- Missing dependencies.
- Unsupported configuration.
- Incorrect initialization order.

**Runtime errors**
- Hardware failure.
- Communication timeout.
- Resource exhaustion.
- Unexpected state.
- Data integrity failure.

**System errors**
- Task deadline violation.
- Watchdog supervision failure.
- Memory corruption.
- Critical service unavailable.

### Error-handling principles

- Detect errors at the appropriate layer.
- Preserve error context.
- Report errors through a consistent interface.
- Distinguish recoverable and non-recoverable faults.
- Avoid silently ignoring failures.
- Avoid unnecessary system resets.
- Define fault escalation.
- Define recovery behavior.
- Avoid recursive error reporting.

A service should not report an error and then continue operating in an undefined state.

## 11. Concurrency and Synchronization

Support both bare-metal and RTOS-based architectures.

Consider:

- Shared state.
- Multiple service clients.
- ISR-to-task communication.
- Task-to-task communication.
- Asynchronous callbacks.
- Reentrant APIs.
- Resource ownership.

Possible synchronization mechanisms:

- Mutexes.
- Semaphores.
- Atomic operations.
- Critical sections.
- Message queues.
- Event flags.
- Single-owner worker tasks.

### Engineering rules

- Use the synchronization primitive appropriate to the execution context.
- Keep critical sections short.
- Avoid blocking inside ISRs.
- Define lock ordering.
- Avoid nested locking unless justified.
- Prevent priority inversion.
- Define timeout behavior.
- Document reentrancy.
- Avoid holding locks during slow hardware operations.

For bare-metal systems, use bounded critical sections and clear producer/consumer ownership.

## 12. Configuration Management

Separate configuration from implementation.

Common configuration types:

- Compile-time configuration.
- Build-time configuration.
- Board configuration.
- Hardware configuration.
- Runtime configuration.
- Persistent configuration.

### Configuration rules

- Avoid magic numbers.
- Use centralized configuration definitions.
- Validate configuration during initialization or build.
- Define default values.
- Define feature dependencies.
- Support multiple hardware variants where required.
- Avoid unnecessary conditional compilation.
- Document configuration ownership.
- Ensure generated configuration is reproducible.

Do not hide architectural differences behind excessive preprocessor macros.

## 13. Portability and Hardware Abstraction

Design BSW services so they can be reused across different MCU platforms.

Separate:

- Generic service logic.
- Platform adaptation.
- Hardware driver implementation.
- Board-specific configuration.

Example:

```text
BSW Service
    |
Platform Interface
    |
    +-- STM32 Implementation
    +-- ESP32 Implementation
    +-- NXP Implementation
    +-- Linux Implementation
```

### Portability rules

- Avoid direct register access in generic service code.
- Avoid vendor HAL types in public portable interfaces.
- Avoid assumptions about interrupt behavior.
- Avoid assumptions about memory architecture.
- Avoid assumptions about timer resolution.
- Avoid assumptions about endianness.
- Avoid assumptions about atomic operations.
- Verify hardware capabilities before selecting an implementation.

Portability does not mean hiding hardware limitations. Expose relevant capabilities through configuration or feature interfaces.

## 14. Security and Reliability

Evaluate each service according to its threat model and failure impact.

Consider:

- Input validation.
- Access control.
- Memory protection.
- Secure storage.
- Authentication.
- Cryptographic integrity.
- Fault detection.
- Recovery.
- Availability.
- Diagnostic information exposure.

For safety-related systems, also consider:

- Fault containment.
- Fail-safe behavior.
- Degraded operation.
- Independent monitoring.
- Safety mechanisms.
- Freedom from interference.

Do not claim functional safety or security compliance merely because defensive coding practices are used. Compliance requires the applicable process, analysis, evidence, and verification.

## 15. Performance and Resource Analysis

BSW must operate within system resource constraints.

Evaluate:

- Flash/ROM consumption.
- RAM consumption.
- Stack usage.
- CPU utilization.
- Interrupt load.
- Communication throughput.
- Service latency.
- Initialization time.
- Memory bandwidth.
- Power consumption.

For a periodic service:

\[
CPU\ Utilization = \frac{Execution\ Time}{Activation\ Period}
\]

For a system with multiple periodic activities, analyze cumulative utilization and worst-case execution time.

### Engineering rules

- Measure before optimizing.
- Avoid unnecessary copies.
- Avoid unnecessary polling.
- Use DMA where justified.
- Avoid dynamic allocation in critical runtime paths unless justified.
- Bound processing time.
- Analyze worst-case behavior, not just average behavior.

## 16. Coding Standards

Follow project coding conventions and applicable coding standards.

For C/C++ embedded development:

- Use fixed-width integer types where appropriate.
- Use `size_t` for memory lengths.
- Validate pointers and parameters.
- Avoid undefined behavior.
- Avoid magic numbers.
- Use explicit state machines.
- Avoid uncontrolled global variables.
- Avoid unnecessary dynamic allocation.
- Avoid unbounded loops.
- Keep ISR execution bounded.
- Document API contracts.
- Document concurrency requirements.
- Separate interface and implementation.
- Keep platform-specific code isolated.

Apply MISRA C, MISRA C++, AUTOSAR C++14, or other standards only when required by the project.

Do not invent compliance claims or suppress static-analysis findings without justification.

## 17. Requirements Engineering

Convert system requirements into measurable BSW requirements.

Example:

**Requirement: Initialization**

The BSW initialization service shall initialize configured software services according to their defined dependency order.

**Requirement: Error reporting**

Each BSW service shall report detected operational errors through the configured error-reporting interface.

**Requirement: Communication abstraction**

The communication service shall provide a hardware-independent interface for configured communication channels.

**Requirement: Persistent storage**

The persistent storage service shall validate stored data before providing it to application software.

**Requirement: Health monitoring**

The system health-monitoring service shall detect configured execution and deadline violations within their specified supervision intervals.

**Requirement: Power management**

The power management service shall prevent entry into a low-power state while configured critical operations remain active.

Each requirement should contain:

- Unique ID.
- Clear shall-statement.
- Preconditions.
- Triggering conditions.
- Expected behavior.
- Timing constraints.
- Error behavior.
- Verification method.
- Traceability to system requirements.

Avoid vague requirements such as "BSW shall be reliable."

## 18. Verification and Testing

Test services independently and as an integrated system.

### Unit tests

Test:

- API parameter validation.
- State transitions.
- Configuration validation.
- Error mapping.
- Timeout behavior.
- Buffer handling.
- Resource management.
- Initialization failure.
- Recovery behavior.

Use mocks and stubs for hardware and operating-system dependencies.

### Integration tests

Test:

- Service-to-service interactions.
- Hardware abstraction interfaces.
- RTOS integration.
- ISR/task communication.
- Asynchronous operations.
- Initialization sequencing.
- Shutdown sequencing.
- Error propagation.
- Resource contention.

### System tests

Test:

- Cold startup.
- Warm restart.
- Reset during operation.
- Power-down and wake-up.
- Communication loss.
- Storage failures.
- Watchdog events.
- Task deadline violations.
- Memory exhaustion.
- Long-duration operation.

### Stress and fault injection

Test:

- Maximum expected communication load.
- Buffer overflow.
- Queue exhaustion.
- Concurrent API calls.
- Hardware disconnection.
- Invalid configuration.
- Timeout conditions.
- Repeated initialization.
- Repeated shutdown.
- Unexpected reset.
- Partial hardware failure.

### Acceptance criteria

- No undefined service states.
- No unbounded waits.
- No memory corruption.
- No uncontrolled resource allocation.
- Correct error reporting.
- Deterministic initialization and shutdown.
- Defined recovery behavior.
- Timing and memory budgets satisfied.
- Hardware dependencies isolated and testable.

## 19. Debugging and Root Cause Analysis

When investigating a BSW issue:

1. Identify the observable failure.
2. Identify the responsible service.
3. Trace the application request through the service interfaces.
4. Check service state.
5. Check initialization dependencies.
6. Check configuration.
7. Check hardware abstraction behavior.
8. Check scheduling and execution context.
9. Check synchronization.
10. Check timeout and error propagation.
11. Reproduce the issue with a focused test.
12. Identify the root cause before changing architecture or implementation.

Common problems include:

- Initialization-order failures.
- Incorrect dependency management.
- Deadlocks.
- Race conditions.
- Buffer overflow.
- Incorrect callback context.
- Missed asynchronous completion.
- Incorrect timeout assumptions.
- Hardware abstraction leaks.
- Resource exhaustion.
- Unhandled partial initialization.
- Inconsistent system state after recovery.

Do not assume every BSW issue originates in the hardware driver.

## 20. Agent Workflow

When asked to implement, modify, review, or debug BSW:

1. Inspect the repository architecture.
2. Identify the target MCU and platform.
3. Identify bare-metal or RTOS execution.
4. Identify the BSW service responsibility.
5. Inspect existing service interfaces.
6. Inspect hardware abstraction and driver dependencies.
7. Identify initialization and scheduling requirements.
8. Identify resource, timing, and memory constraints.
9. Define service state and error behavior.
10. Define API and ownership contracts.
11. Implement generic service logic.
12. Implement platform-specific adaptation separately.
13. Add unit tests and mocks.
14. Add integration tests.
15. Run builds, static analysis, and available tests.
16. Review concurrency, timing, and recovery behavior.
17. Document assumptions and limitations.

### Before modifying code

Inspect:

- Existing BSW architecture.
- Public headers.
- Service implementation.
- Hardware abstraction interfaces.
- OS abstraction interfaces.
- Configuration files.
- Build system.
- Startup and shutdown code.
- Existing tests.

Do not create a new abstraction if an existing project interface already provides the required functionality.

### When information is missing

Do not invent:

- Hardware capabilities.
- Execution context.
- Timing requirements.
- Memory limits.
- OS behavior.
- Error recovery guarantees.
- Platform-specific API behavior.

Use explicit assumptions and identify information that must be confirmed.

## 21. Expected Deliverables

Depending on the task, produce:

- BSW architecture and design.
- Service responsibility definition.
- Dependency diagrams.
- Portable service interfaces.
- Platform adaptation interfaces.
- Service implementation.
- State-machine design.
- Initialization and shutdown design.
- Configuration definitions.
- Error-handling strategy.
- Timing and resource analysis.
- Unit and integration tests.
- Fault-injection test cases.
- Requirements and traceability.
- Technical documentation.

## 22. Senior Engineering Decision Principles

1. BSW provides reusable infrastructure, not application-specific business logic.
2. Separate generic service logic from hardware-dependent implementation.
3. Define service responsibilities and dependencies explicitly.
4. Design APIs around clear contracts and ownership.
5. Treat initialization and shutdown as controlled system processes.
6. Define execution context and concurrency behavior for every important API.
7. Use deterministic resource management where practical.
8. Make errors observable and recovery behavior explicit.
9. Validate timing and resource usage at system level.
10. Prefer existing platform capabilities over unnecessary custom frameworks.
11. Do not introduce abstraction without a meaningful architectural benefit.
12. Ensure every service is independently testable.
13. Preserve portability without hiding hardware limitations.
14. Treat reliability, security, and maintainability as design requirements from the beginning.

The goal is to build reusable, portable, deterministic, and testable embedded software infrastructure that can support different MCUs, operating systems, hardware platforms, and application architectures.
