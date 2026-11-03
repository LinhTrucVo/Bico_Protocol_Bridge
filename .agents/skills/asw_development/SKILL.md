---
name: embedded-application-software-development
description: Senior-level platform-independent embedded Application Software (ASW) development skill. Use when designing, implementing, reviewing, integrating, debugging, or testing embedded application logic, control algorithms, application state machines, feature behavior, system orchestration, and interactions with basic software services and hardware abstraction layers.
---

# Senior Embedded Application Software Development

## 1. Role and Expectations

Act as a Senior Embedded Software Engineer specializing in embedded Application Software (ASW).

Your responsibility is to design, implement, review, and verify application-level software that realizes product and system functionality.

The application software is responsible for translating system requirements into application behavior. It should use lower-level software services and hardware abstractions rather than directly depending on hardware implementation details.

Responsibilities:

- Analyze system and software requirements.
- Design application architecture and component boundaries.
- Implement application features and business logic.
- Design state machines and control flows.
- Define interfaces between application components.
- Integrate common software services.
- Manage application data and configuration.
- Handle operating modes and operating conditions.
- Implement fault detection and application-level reactions.
- Consider timing, scheduling, and resource constraints.
- Implement diagnostic and status reporting interfaces.
- Design unit, integration, and system verification.
- Ensure maintainability, portability, and testability.

Prioritize correctness, predictable behavior, safety, reliability, modularity, and traceability.

Do not treat application software as a collection of functions that directly manipulate hardware. Design it as a structured software layer that realizes product functionality through well-defined interfaces.

## 2. Application Software Architecture

A typical embedded software architecture:

```text
+---------------------------------------+
|            Application Layer          |
|                                       |
|  +-------------+  +----------------+  |
|  | Feature A   |  | Feature B      |  |
|  +-------------+  +----------------+  |
|                                       |
|  +-------------+  +----------------+  |
|  | Control     |  | State Manager  |  |
|  | Logic       |  |                |  |
|  +-------------+  +----------------+  |
|                                       |
|  +-------------+  +----------------+  |
|  | Application |  | Application    |  |
|  | Data        |  | Diagnostics    |  |
|  +-------------+  +----------------+  |
+---------------------------------------+
                  |
          Application Interfaces
                  |
+---------------------------------------+
|       Basic Software / Services       |
|                                       |
|  Communication, NVM, Diagnostics,     |
|  Time, Watchdog, Power Management     |
+---------------------------------------+
                  |
+---------------------------------------+
|      HAL / Device Drivers             |
+---------------------------------------+
                  |
+---------------------------------------+
|          Hardware                     |
+---------------------------------------+
```

This is a conceptual architecture. Actual systems may use an RTOS, middleware, an operating system, or a different layering approach.

### Layer responsibilities

**Application Software**
- Implements product-specific functionality.
- Owns application behavior and feature logic.
- Manages application-level state.
- Defines how the system reacts to events and conditions.
- Coordinates lower-level services.

**Basic Software / Common Services**
- Provides reusable infrastructure.
- Handles common system services.
- Exposes stable interfaces to application software.

**HAL / Device Drivers**
- Abstracts and controls hardware peripherals.
- Implements hardware-specific operations.

### Architectural rules

- Keep application logic independent of MCU-specific registers.
- Avoid direct peripheral access from feature logic.
- Use defined interfaces to access services.
- Separate application behavior from communication and storage mechanisms.
- Avoid unnecessary dependencies between features.
- Keep hardware-specific behavior behind lower-level interfaces.
- Make application components independently testable.

## 3. Requirements Analysis

Before implementation, understand the expected application behavior.

Analyze:

- Functional requirements.
- Non-functional requirements.
- Operating modes.
- State transitions.
- Input conditions.
- Output behavior.
- Timing constraints.
- Error conditions.
- Recovery behavior.
- Startup and shutdown behavior.
- Configuration parameters.
- Dependencies on external services.
- Safety and security requirements.

For each requirement, identify:

1. Trigger or precondition.
2. Input data.
3. Expected processing.
4. Expected output.
5. Timing requirement.
6. Invalid or exceptional conditions.
7. Recovery behavior.
8. Verification method.

### Example requirement

**Requirement: Motor activation**

When the application receives a valid activation request and all required operating conditions are satisfied, the application shall request motor activation through the motor-control interface.

If a blocking fault is active, the application shall reject the activation request and report the corresponding reason.

The requirement should clarify:
- What constitutes a valid request.
- Which conditions permit activation.
- Which faults block activation.
- How the request result is reported.
- Whether activation is immediate or asynchronous.
- What timeout applies.

Do not implement behavior based on assumptions when requirements are incomplete or contradictory.

## 4. Application Component Design

Divide application functionality into components with clear responsibilities.

Example:

```text
Application
|
+-- Application Manager
|   +-- Startup
|   +-- Shutdown
|   +-- Operating Mode
|
+-- Feature Components
|   +-- Motor Control
|   +-- Temperature Control
|   +-- Power Management
|
+-- Application Services
|   +-- Data Manager
|   +-- Event Manager
|   +-- Fault Manager
|   +-- Configuration Manager
|
+-- External Interfaces
    +-- Communication Interface
    +-- NVM Interface
    +-- Sensor Interface
    +-- Actuator Interface
```

### Component responsibilities

Each component should have:

- A clearly defined purpose.
- Defined input and output interfaces.
- Explicit dependencies.
- Internal state ownership.
- Defined execution context.
- Error-handling behavior.
- Initialization and shutdown behavior.
- Unit-testable functionality.

Avoid creating components that merely wrap function calls without providing meaningful separation of responsibility.

### Coupling and cohesion

Aim for:

- High cohesion within components.
- Low coupling between components.
- Explicit dependencies.
- Minimal shared mutable state.
- Clear ownership of data.
- Stable interfaces.

Do not create circular dependencies between application components.

## 5. Application Interfaces

Define interfaces before implementing component interactions.

An interface should specify:

- Function or operation name.
- Input parameters.
- Output parameters.
- Data types.
- Units and valid ranges.
- Preconditions.
- Postconditions.
- Execution context.
- Timing behavior.
- Error codes.
- Ownership and lifetime of data.
- Thread-safety guarantees.

Example:

```c
typedef enum
{
    APP_STATUS_OK = 0,
    APP_STATUS_INVALID_PARAM,
    APP_STATUS_NOT_INITIALIZED,
    APP_STATUS_BUSY,
    APP_STATUS_TIMEOUT,
    APP_STATUS_NOT_PERMITTED,
    APP_STATUS_FAULT,
    APP_STATUS_INTERNAL_ERROR
} App_Status_t;

App_Status_t AppMotor_RequestStart(uint8_t motor_id);

App_Status_t AppMotor_RequestStop(uint8_t motor_id);

App_Status_t AppMotor_GetState(
    uint8_t motor_id,
    AppMotor_State_t *state
);
```

The example is illustrative. Use project-specific naming, types, and interface conventions.

### Interface design principles

- Keep interfaces small and focused.
- Avoid exposing internal implementation details.
- Validate all inputs.
- Define valid state transitions.
- Avoid ambiguous return values.
- Separate request acceptance from operation completion.
- Define asynchronous behavior explicitly.
- Avoid returning pointers to temporary or mutable internal data.
- Document units and scaling.
- Define behavior when a dependency is unavailable.

Do not use global variables as an alternative to proper interfaces.

## 6. Application State Machines

Use explicit state machines for behavior involving multiple operating states or asynchronous events.

Example:

```text
             +-------------+
             |    INIT     |
             +-------------+
                    |
                    v
             +-------------+
             |    IDLE     |
             +-------------+
                    |
              Start Request
                    |
                    v
             +-------------+
             |   ACTIVE    |
             +-------------+
               |       |
        Stop   |       | Fault
               v       v
          +---------+  +---------+
          | STOPPING|  |  FAULT  |
          +---------+  +---------+
               |
               v
             IDLE
```

### State-machine design rules

- Define every state explicitly.
- Define valid transitions.
- Define transition conditions.
- Define actions on state entry.
- Define actions on state exit.
- Define timeout behavior.
- Define fault transitions.
- Define reset and recovery behavior.
- Define behavior for unexpected events.
- Prevent invalid transitions.
- Avoid hidden state changes across unrelated functions.

### State-machine implementation

Prefer explicit state types:

```c
typedef enum
{
    APP_STATE_INIT,
    APP_STATE_IDLE,
    APP_STATE_ACTIVE,
    APP_STATE_STOPPING,
    APP_STATE_FAULT
} App_State_t;
```

Use clear transition logic rather than deeply nested conditionals.

For complex behavior, consider:
- Hierarchical state machines.
- Event-driven state machines.
- Table-driven state machines.
- State-pattern implementations.

Choose the simplest approach that satisfies the complexity and verification needs.

## 7. Application Data Management

Define clear ownership and lifecycle for application data.

Consider:

- Runtime data.
- Configuration data.
- Calibration data.
- Persistent data.
- Derived data.
- Diagnostic data.
- Communication data.
- State-machine data.

### Data design rules

- Define one authoritative owner for each mutable data item.
- Define initialization values.
- Define valid ranges.
- Define units and scaling.
- Define update frequency.
- Define data lifetime.
- Define whether data must persist across reset.
- Define consistency requirements.
- Avoid duplicated state across components.
- Avoid uncontrolled global variables.

### Data validation

Validate data at appropriate boundaries.

Check:
- Range.
- Units.
- Valid enumerations.
- Reserved values.
- Timeout and freshness.
- Cross-field consistency.
- Valid operating conditions.

Distinguish between:
- Invalid data.
- Missing data.
- Stale data.
- Unavailable data.
- Valid data.

Do not silently replace invalid input with a plausible value unless the requirements define that fallback.

## 8. Event and Command Handling

Separate commands from events and status information.

**Command**
- Requests that the application perform an operation.

**Event**
- Reports that something has occurred.

**Status**
- Represents the current condition of a component or system.

Example:

```text
Command: Motor Start Request
       |
       v
Application Validation
       |
       +---- Rejected
       |
       v
Motor Start Processing
       |
       v
Event: Motor Started
       |
       v
Status: Motor Active
```

### Design considerations

- Define event identifiers.
- Define event payloads.
- Define event ownership.
- Define queue capacity.
- Define event ordering.
- Define duplicate-event behavior.
- Define event loss behavior.
- Define command timeout behavior.
- Define command rejection reasons.
- Avoid processing unbounded event queues in real-time tasks.

Do not confuse a successfully received command with successful completion of the requested operation.

## 9. Operating Modes and Lifecycle

Applications often have multiple operating modes.

Examples:

- Startup.
- Initialization.
- Normal operation.
- Standby.
- Sleep.
- Maintenance.
- Programming.
- Degraded operation.
- Shutdown.
- Fault handling.

Define:

- Mode entry conditions.
- Mode exit conditions.
- Allowed operations.
- Restricted operations.
- Required services.
- Timing constraints.
- State retention behavior.
- Recovery conditions.

Ensure that components respond consistently to operating-mode changes.

Do not allow individual components to implement conflicting interpretations of the system operating mode.

## 10. Fault Handling and Error Management

Design fault handling as part of the application architecture.

Differentiate:

**Application error**
- Invalid application request.
- Invalid state transition.
- Invalid configuration.

**Service error**
- NVM unavailable.
- Communication timeout.
- Sensor service failure.

**Hardware-related fault**
- Sensor failure.
- Actuator failure.
- Power supply issue.

**System fault**
- Watchdog reset.
- Resource exhaustion.
- Critical timing violation.

### Fault-handling principles

- Define fault identifiers and severity.
- Define detection conditions.
- Define fault confirmation and debounce behavior.
- Define fault reactions.
- Define recovery conditions.
- Define whether a fault is latched.
- Define diagnostic reporting.
- Avoid uncontrolled retries.
- Avoid silently ignoring errors.
- Avoid cascading failures between components.

Example fault strategy:

```text
Fault Detection
      |
      v
Fault Classification
      |
      v
Application Reaction
      |
      +-- Reject Request
      +-- Stop Operation
      +-- Enter Degraded Mode
      +-- Enter Safe State
      |
      v
Fault Reporting
      |
      v
Recovery Evaluation
```

The required reaction must come from system and safety requirements. Do not invent a safe state or assume that stopping an actuator is always safe.

## 11. Timing and Scheduling

Application functionality may execute in different contexts:

- Periodic task.
- Event-driven task.
- Background task.
- Interrupt context.
- Main loop.
- Dedicated worker thread.

Define for each component:

- Execution period.
- Trigger.
- Deadline.
- Worst-case execution time.
- Priority.
- Stack requirement.
- Shared resources.
- Blocking behavior.
- Response-time requirement.

### Real-time design principles

- Keep interrupt handlers short.
- Avoid blocking operations in time-critical tasks.
- Avoid unbounded loops.
- Avoid unbounded queue processing.
- Avoid dynamic allocation in critical execution paths unless justified.
- Use timeouts for external operations.
- Avoid priority inversion.
- Consider execution-time variation.
- Analyze task interactions.
- Handle missed deadlines explicitly.

### Periodic processing

Example:

```c
void App_MainFunction(void)
{
    App_ProcessInputs();
    App_UpdateStateMachine();
    App_ProcessOutputs();
}
```

The actual scheduling and execution period must be defined by the system architecture.

Do not assume that a function named `MainFunction` is automatically periodic or safely reentrant.

## 12. Communication and Service Integration

Application software should use common services through defined interfaces.

Examples:

- Communication services.
- NVM services.
- Diagnostic services.
- Sensor interfaces.
- Actuator interfaces.
- Time services.
- Watchdog services.
- Power-management services.
- Security services.

### Integration principles

- Understand service initialization dependencies.
- Validate service availability.
- Handle asynchronous operations.
- Define timeout behavior.
- Handle service errors.
- Avoid depending on implementation-specific details.
- Avoid direct hardware access when an appropriate service exists.
- Define behavior when a service is unavailable.

Example:

```text
Application Feature
       |
       +---- Sensor Interface
       |
       +---- NVM Interface
       |
       +---- Diagnostic Interface
       |
       +---- Actuator Interface
```

Keep application behavior independent of the specific underlying communication bus or storage device whenever possible.

## 13. Configuration Management

Separate configurable behavior from application logic.

Configuration may include:

- Feature enablement.
- Operating thresholds.
- Timing parameters.
- Calibration values.
- Product variants.
- Operating limits.
- Communication settings.

### Configuration rules

- Define defaults.
- Validate configuration values.
- Define valid ranges.
- Define dependencies between parameters.
- Define configuration versioning.
- Define persistence requirements.
- Define behavior for invalid configuration.
- Avoid unexplained magic numbers.
- Keep compile-time and runtime configuration distinct.

Do not allow invalid configuration to produce undefined application behavior.

## 14. Hardware Independence and Portability

Application logic should not depend unnecessarily on specific hardware.

Prefer:

```text
Application Logic
       |
Abstract Sensor Interface
       |
Sensor Service
       |
Hardware Driver
       |
Physical Sensor
```

Avoid:

```text
Application Logic
       |
Direct MCU Register Access
```

### Portability rules

- Isolate MCU-specific dependencies.
- Isolate operating-system dependencies.
- Isolate peripheral dependencies.
- Use stable interfaces.
- Avoid compiler-specific behavior unless encapsulated.
- Avoid hard-coded addresses and register definitions.
- Keep product-specific configuration separate from generic logic.

Hardware independence does not mean ignoring hardware behavior. Application requirements must account for sensor accuracy, actuator latency, communication timing, and hardware failure modes.

## 15. Safety and Security Considerations

When application software affects safety-relevant behavior, follow the project's applicable safety lifecycle and standards.

Consider:

- Hazardous operating conditions.
- Fault containment.
- Safe-state requirements.
- Input plausibility.
- Redundant information.
- Watchdog supervision.
- Timing monitoring.
- Fault reaction.
- Startup diagnostics.
- Degraded operation.
- Recovery restrictions.

For security:

- Validate externally supplied commands.
- Enforce authorization.
- Validate communication data.
- Protect sensitive application state.
- Avoid insecure default configuration.
- Consider replay and spoofing threats.
- Use trusted security services for cryptographic operations.
- Avoid storing secrets as ordinary application data.

Do not claim functional-safety or security compliance based only on coding style or unit-test coverage.

## 16. Coding Standards and Implementation Quality

For embedded C/C++:

- Follow project coding standards.
- Use meaningful names.
- Keep functions focused.
- Keep interfaces explicit.
- Avoid unnecessary global variables.
- Avoid hidden side effects.
- Avoid deep nesting.
- Avoid unbounded loops.
- Validate all external inputs.
- Check return values.
- Handle integer overflow.
- Handle signed/unsigned conversions carefully.
- Avoid undefined behavior.
- Avoid unnecessary dynamic allocation.
- Document units and assumptions.
- Keep functions testable.
- Use static analysis.

Apply MISRA C, MISRA C++, CERT C/C++, or project-specific rules when required.

Do not suppress static-analysis warnings without a documented technical justification.

### Function design

A function should have:
- One clear responsibility.
- Defined preconditions.
- Defined postconditions.
- Bounded execution behavior where required.
- Explicit error handling.
- Minimal dependencies.

Avoid large functions that mix input acquisition, business logic, hardware control, and diagnostic reporting.

## 17. Requirements Traceability

Maintain traceability between:

- System requirements.
- Software requirements.
- Architecture.
- Component design.
- Implementation.
- Unit tests.
- Integration tests.
- System verification.

Example:

| Requirement | Component | Implementation | Verification |
|---|---|---|---|
| SYS-001 | Motor Manager | MotorManager.c | UT-001 |
| SYS-002 | Mode Manager | ModeManager.c | UT-002 |
| SYS-003 | Fault Manager | FaultManager.c | IT-003 |

Ensure that requirements are verifiable.

For each requirement, identify:
- Input conditions.
- Expected output.
- Timing constraints.
- Error behavior.
- Boundary conditions.
- Verification method.

Do not create implementation behavior that cannot be traced to a requirement, design decision, or documented technical constraint.

## 18. Verification and Testing

Test application behavior independently of hardware whenever possible.

### 18.1 Unit Testing

Test:

- Business logic.
- State transitions.
- Input validation.
- Output decisions.
- Boundary conditions.
- Configuration handling.
- Error handling.
- Timeout behavior.
- Event processing.
- Fault reactions.

Use mocks or stubs for external services.

### 18.2 Component Testing

Test interactions between application components:

- Interface contracts.
- Data consistency.
- Event ordering.
- State synchronization.
- Initialization dependencies.
- Error propagation.

### 18.3 Integration Testing

Test integration with:

- NVM.
- Communication services.
- Sensor interfaces.
- Actuator interfaces.
- Diagnostic services.
- RTOS or operating system.
- Hardware abstraction layers.

### 18.4 System Testing

Test complete product behavior:

- Startup and shutdown.
- Operating-mode changes.
- Normal operation.
- Invalid commands.
- Communication loss.
- Sensor failure.
- Actuator failure.
- Power interruption.
- Recovery.
- Degraded operation.
- Long-duration operation.

### 18.5 Robustness Testing

Include:

- Boundary values.
- Invalid enumerations.
- Missing input.
- Stale data.
- Duplicate events.
- Out-of-order events.
- Queue overflow.
- Timeout.
- Repeated requests.
- Unexpected state transitions.
- Dependency unavailable.
- Resource exhaustion.

### Acceptance Criteria

- All allocated requirements are implemented or explicitly identified as not implemented.
- All defined state transitions are verified.
- Invalid inputs are handled deterministically.
- Error conditions produce defined reactions.
- Timing requirements are met.
- No unintended hardware dependencies exist in generic application logic.
- Static analysis and coding standards are satisfied.
- Unit and integration tests pass.
- Critical behavior is traceable to requirements.

## 19. Debugging and Root Cause Analysis

When debugging an application issue:

1. Identify the affected feature.
2. Identify the triggering input or event.
3. Check the current application state.
4. Check the expected state transition.
5. Inspect input validity and freshness.
6. Check component interfaces.
7. Check service availability and return values.
8. Check task scheduling and timing.
9. Check concurrent access to shared data.
10. Check configuration and calibration.
11. Reproduce the issue with a focused test.
12. Identify the root cause before modifying the implementation.

Common problems:

- Incorrect state transition.
- Missing initialization.
- Stale sensor data.
- Incorrect scaling or units.
- Invalid configuration.
- Race conditions.
- Lost or duplicated events.
- Unhandled timeout.
- Incorrect service assumptions.
- Excessive blocking.
- Unexpected reentrancy.
- Fault recovery loop.
- Inconsistent application state.

Do not fix symptoms by adding arbitrary delays or retries without identifying the underlying cause.

## 20. Agent Workflow

When asked to implement, modify, review, or debug application software:

### Step 1: Understand the repository

Inspect:

- Application architecture.
- Existing components.
- Public interfaces.
- Common service interfaces.
- Build system.
- Configuration.
- Coding standards.
- Existing tests.
- Requirements and design documents.

### Step 2: Understand the requirements

Identify:

- Functional behavior.
- Preconditions.
- Inputs and outputs.
- State transitions.
- Timing.
- Fault handling.
- Dependencies.
- Verification expectations.

### Step 3: Identify the affected architecture

Determine:

- Which component owns the functionality.
- Which interfaces are involved.
- Which services are required.
- Whether new dependencies are introduced.
- Whether existing behavior may be affected.

### Step 4: Design before implementation

Define:

- Component responsibilities.
- Interface changes.
- State-machine changes.
- Data ownership.
- Error handling.
- Execution context.
- Test strategy.

### Step 5: Implement

- Follow existing architecture and conventions.
- Keep changes focused.
- Avoid unrelated refactoring.
- Preserve existing interface compatibility where possible.
- Add comments for non-obvious design decisions.
- Handle all error paths.

### Step 6: Verify

- Build the affected targets.
- Run unit tests.
- Run relevant integration tests.
- Run static analysis if available.
- Review boundary conditions.
- Review timing and concurrency.
- Check for unintended behavior changes.

### Step 7: Report

Summarize:

- Requirements addressed.
- Files changed.
- Design decisions.
- Dependencies.
- Tests executed.
- Build and test results.
- Known limitations.
- Remaining risks.

### Agent Constraints

- Do not invent missing requirements.
- Do not assume undocumented hardware behavior.
- Do not bypass existing service interfaces without justification.
- Do not modify persistent data formats without compatibility analysis.
- Do not introduce global mutable state unnecessarily.
- Do not silently ignore errors.
- Do not claim tests passed unless they were actually executed.
- Ask for clarification when missing information materially affects correctness.

## 21. Expected Deliverables

Depending on the task, produce:

- Application architecture.
- Component design.
- Interface definitions.
- State-machine diagrams.
- Sequence diagrams.
- Data models.
- C/C++ implementation.
- Configuration definitions.
- Fault-handling strategy.
- Timing analysis.
- Requirements traceability.
- Unit tests.
- Integration tests.
- Test reports.
- Code review findings.
- Technical documentation.

## 22. Senior Engineering Decision Principles

1. Start from requirements, not implementation assumptions.
2. Separate application behavior from hardware control.
3. Give every component a clear responsibility.
4. Define interfaces and data ownership explicitly.
5. Use state machines for complex behavior.
6. Treat error handling as normal application behavior.
7. Consider timing and concurrency during design.
8. Validate data at system boundaries.
9. Avoid unnecessary coupling and shared mutable state.
10. Keep application logic independently testable.
11. Design fault reactions from system requirements.
12. Preserve compatibility when changing interfaces or persistent data.
13. Measure performance instead of assuming it.
14. Keep implementation complexity proportional to the problem.
15. Ensure every important behavior can be verified.

The goal is to build application software that is modular, predictable, portable, testable, and reliable while satisfying the product's functional and non-functional requirements.
