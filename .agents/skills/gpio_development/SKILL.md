---
name: embedded-gpio-development
description: Senior-level guidance for developing, reviewing, testing, and documenting GPIO drivers and GPIO-based embedded services in C/C++ projects. Use when implementing GPIO input/output, pin configuration, interrupts, edge detection, debouncing, alternate functions, low-power behavior, hardware abstraction, and GPIO diagnostics for STM32, ESP32, and other MCUs.
---

# Embedded GPIO Development — Senior Engineer Skill

## 1. Role and Engineering Expectations

Act as a Senior Embedded Software Engineer specializing in GPIO development.

Your responsibilities include:

- Analyze GPIO requirements before implementation.
- Understand MCU pin capabilities and electrical constraints.
- Design reusable and portable GPIO interfaces.
- Implement MCU-specific GPIO hardware abstraction.
- Develop reliable input and output handling.
- Implement interrupt and event-driven GPIO processing.
- Handle concurrency and real-time constraints.
- Implement diagnostics and fault handling where applicable.
- Develop unit, integration, and hardware tests.
- Review GPIO code for reliability, portability, safety, and maintainability.

Prioritize hardware correctness and predictable behavior over unnecessary abstraction.

Never assume that GPIO capabilities are identical across MCU families or even between pins of the same MCU.

## 2. Supported Platforms

Primary platforms:

- STM32 (F0/F1/F4/G4/L4/H7 and other families).
- ESP32 (ESP32, ESP32-C3, ESP32-S3 and other variants).

The architecture should allow additional MCU platforms.

### Platform-specific rules

1. Consult the exact MCU datasheet and reference manual.
2. Verify pin availability and GPIO capabilities.
3. Check pin multiplexing and alternate functions.
4. Verify input/output voltage limits.
5. Check maximum output current and total port current.
6. Verify internal pull-up and pull-down support.
7. Check interrupt and wake-up capabilities.
8. Identify bootstrapping, strapping, and reserved pins.
9. Check pins shared with debugging interfaces, flash, USB, or other peripherals.
10. Verify behavior during reset, startup, and low-power modes.

Do not invent GPIO APIs, pin mappings, register definitions, or electrical capabilities.

## 3. GPIO Fundamentals

Understand the following concepts.

### GPIO operating modes

- Input mode.
- Output mode.
- Alternate-function mode.
- Analog mode.
- High-impedance input.
- Open-drain output.
- Push-pull output.

### GPIO electrical characteristics

- Logic HIGH and LOW.
- Input voltage thresholds.
- Output HIGH/LOW voltage.
- Output drive strength.
- Maximum source/sink current.
- Input leakage current.
- Pin capacitance.
- Rise and fall time.
- Pull-up and pull-down resistance.
- Floating input behavior.
- 3.3 V and 5 V compatibility.
- Absolute maximum ratings.

### GPIO terminology

Understand the distinction between:

- Active HIGH and active LOW.
- Physical pin state and logical signal state.
- Input sampling and output driving.
- Open-drain and push-pull.
- GPIO and alternate-function peripheral control.
- Internal and external pull resistors.

Do not assume that a logical TRUE always corresponds to a physical HIGH level.

## 4. GPIO Configuration Parameters

Design configuration structures to support applicable parameters.

| Parameter | Description |
|---|---|
| Pin identifier | MCU-specific pin or port/pin |
| Direction | Input or output |
| Output type | Push-pull or open-drain |
| Pull configuration | None, pull-up, pull-down |
| Output initial state | LOW or HIGH |
| Drive strength | Configurable drive capability |
| Slew rate | Output transition speed |
| Alternate function | Peripheral pin assignment |
| Interrupt mode | Disabled, rising, falling, both edges |
| Interrupt priority | Platform-specific priority |
| Debounce configuration | Software or hardware filtering |
| Wake-up configuration | Low-power wake-up capability |

Only expose settings supported by the target MCU.

Keep hardware-specific settings separate from application-level signal configuration.

## 5. GPIO Input Development

Support the following input operations:

- Initialize input pin.
- Read input state.
- Configure pull-up.
- Configure pull-down.
- Configure floating input.
- Detect logical state transitions.
- Handle active-low signals.
- Handle active-high signals.

### Input design considerations

1. Floating inputs must be avoided unless explicitly required.
2. External pull resistors may be necessary.
3. Input voltage must remain within the MCU electrical limits.
4. Consider signal noise and contact bounce.
5. Consider input synchronization and sampling latency.
6. Define behavior when the input is disconnected.
7. Define the expected state during reset and initialization.

### Logical abstraction

Application code should preferably use logical signal states rather than direct electrical assumptions.

Example:

```c
typedef enum
{
    GPIO_LOGICAL_INACTIVE = 0,
    GPIO_LOGICAL_ACTIVE
} Gpio_LogicalState_t;
```

For active-low signals, the GPIO service should handle electrical-to-logical conversion.

## 6. GPIO Output Development

Support:

- Initialize output pin.
- Set output HIGH.
- Set output LOW.
- Toggle output.
- Read output state where meaningful.
- Configure initial output state.
- Configure push-pull or open-drain.

### Output design considerations

1. Define the required output state before enabling output mode.
2. Avoid unintended output pulses during initialization.
3. Consider active-low output behavior.
4. Verify output current limits.
5. Verify whether external pull resistors are required.
6. Consider reset and boot-time output behavior.
7. Avoid toggling outputs from multiple uncontrolled execution contexts.

### Glitch-free initialization

When supported by the hardware, preload the desired output value before switching the pin into output mode.

The implementation must consider platform-specific register behavior and avoid unintended transitions.

### Output state abstraction

Provide application-level operations such as:

- Activate signal.
- Deactivate signal.
- Toggle signal.

Do not force application logic to understand physical polarity.

## 7. GPIO Interrupt and Event Handling

Support applicable interrupt configurations:

- Rising edge.
- Falling edge.
- Both edges.
- High-level trigger.
- Low-level trigger.
- Interrupt enable/disable.
- Interrupt status handling.
- Event notification.

### Interrupt design principles

1. Keep interrupt service routines short.
2. Avoid blocking operations inside ISRs.
3. Avoid dynamic memory allocation inside ISRs.
4. Avoid logging operations with unpredictable execution time.
5. Do not perform complex application processing inside ISRs.
6. Use appropriate synchronization when sharing data with tasks.
7. Handle interrupt flags correctly.
8. Consider interrupt priority and latency.
9. Prevent event loss where event delivery is critical.
10. Document whether callbacks execute in ISR or task context.

### Event-driven architecture

Prefer this architecture:

GPIO Hardware Interrupt
    -> ISR
    -> Event notification / queue
    -> Application task
    -> Application processing

Do not assume an interrupt callback executes in normal thread context.

## 8. Debouncing and Signal Filtering

Mechanical switches and noisy external signals may generate multiple transitions for one logical event.

Support appropriate techniques:

### Software debounce

- Time-based debounce.
- Stable-state sampling.
- State-machine-based debounce.

### Hardware debounce

- RC filtering.
- Schmitt-trigger input.
- Dedicated hardware filtering where supported.

### Example state-machine concept

```c
typedef enum
{
    GPIO_DEBOUNCE_IDLE,
    GPIO_DEBOUNCE_VERIFY,
    GPIO_DEBOUNCE_CONFIRMED
} Gpio_DebounceState_t;
```

The debounce implementation should:

1. Detect an initial transition.
2. Start a verification interval.
3. Sample the input again after the configured interval.
4. Confirm the event only when the signal remains stable.
5. Avoid blocking delays.

Define whether debounce applies to both edges and whether it introduces additional event latency.

Do not apply debounce indiscriminately to high-frequency signals such as encoder inputs.

## 9. Alternate Function and Pin Multiplexing

GPIO pins are frequently shared with peripheral functions.

Examples:

- UART TX/RX.
- SPI MOSI/MISO/SCLK.
- I2C SDA/SCL.
- CAN TX/RX.
- PWM output.
- Timer capture.
- ADC input.
- USB.
- Ethernet.
- External memory interfaces.

The GPIO development process must:

1. Verify alternate-function mapping.
2. Check peripheral pin requirements.
3. Detect pin conflicts.
4. Avoid reconfiguring pins owned by another peripheral.
5. Respect peripheral initialization order.
6. Restore appropriate pin states when peripherals are disabled.
7. Document pin ownership.

Do not treat alternate-function pins as ordinary GPIO while the peripheral is using them.

## 10. Low-Power and Reset Behavior

Consider GPIO behavior across:

- Power-on reset.
- Software reset.
- Watchdog reset.
- Deep sleep.
- Standby.
- Shutdown.
- Wake-up.
- Peripheral clock disable.

Verify:

- Default pin state.
- Retention behavior.
- Wake-up capability.
- Pull resistor behavior.
- Output state restoration.
- Leakage current.
- Unintended peripheral activation.

Do not assume output states are retained across every low-power mode.

## 11. GPIO Diagnostics and Error Handling

Potential diagnostics include:

| Diagnostic | Purpose |
|---|---|
| Invalid pin configuration | Detect unsupported configuration |
| Pin ownership conflict | Prevent conflicting peripheral usage |
| Input plausibility | Detect unexpected signal state |
| Stuck-at HIGH | Detect input remaining HIGH unexpectedly |
| Stuck-at LOW | Detect input remaining LOW unexpectedly |
| Transition timeout | Detect missing expected transitions |
| Output feedback mismatch | Compare commanded output with independent feedback |
| Initialization failure | Report hardware configuration failure |

Important limitations:

- Standard GPIO hardware does not automatically detect every electrical fault.
- Detecting open circuits requires appropriate circuit design.
- Detecting output faults may require external feedback.
- Stuck-at detection requires application-specific expected behavior.
- A software readback of an output register does not prove the physical pin reached the expected voltage.

Do not report electrical fault detection unless the hardware supports it.

## 12. Software Architecture

Prefer a layered architecture.

Application Layer:
- LED control.
- Button handling.
- Relay control.
- External device control.
- Digital input monitoring.

GPIO Service Layer:
- Logical signal abstraction.
- Active-high/active-low conversion.
- Debouncing.
- Event processing.
- Signal diagnostics.

GPIO Hardware Abstraction Layer:
- Initialization.
- Input read.
- Output write.
- Toggle.
- Interrupt configuration.
- Pin configuration.

MCU-specific Driver:
- STM32 HAL/LL or register-level implementation.
- ESP-IDF GPIO driver.
- Other MCU-specific GPIO implementations.

### Architecture rules

1. Keep application logic independent of MCU-specific APIs.
2. Isolate platform-specific implementation.
3. Use explicit pin configuration.
4. Avoid hidden global pin ownership.
5. Define initialization and shutdown behavior.
6. Define interrupt execution context.
7. Make shared-state synchronization explicit.
8. Avoid unnecessary dynamic allocation.
9. Keep hardware initialization deterministic.
10. Avoid unnecessary abstraction for simple GPIO operations.

## 13. Coding Standards

Follow embedded C/C++ best practices.

### C requirements

- Use fixed-width integer types.
- Use enumerations for operating modes.
- Use explicit error codes.
- Avoid magic numbers.
- Validate configuration parameters.
- Validate pointers.
- Avoid undefined behavior.
- Avoid implicit narrowing conversions.
- Document pin polarity and electrical meaning.
- Keep ISRs short and deterministic.

### C++ requirements

- Prefer RAII where appropriate.
- Use clear ownership of GPIO resources.
- Use strongly typed pin and signal configurations where beneficial.
- Avoid unnecessary heap allocation.
- Avoid exceptions if prohibited by project constraints.
- Isolate MCU-specific GPIO access behind interfaces.

### General requirements

- Follow existing project coding conventions.
- Follow MISRA C/C++ when required.
- Avoid unnecessary global state.
- Avoid blocking delays in real-time critical code.
- Do not silently ignore hardware errors.

## 14. Requirements Engineering

Before implementation, identify:

1. Exact MCU and package.
2. SDK/HAL version.
3. GPIO port and pin mapping.
4. Pin direction.
5. Active-high or active-low behavior.
6. Input or output electrical requirements.
7. Pull-up/pull-down requirements.
8. Output drive strength.
9. Required initial state.
10. Interrupt requirements.
11. Debounce requirements.
12. Timing and latency constraints.
13. Alternate-function ownership.
14. Reset and low-power behavior.
15. Diagnostic requirements.

Translate requirements into measurable software requirements.

### Example requirements

**GPIO_REQ_001 — Input initialization**

The software shall configure the specified GPIO pin as an input with the configured pull resistor.

**GPIO_REQ_002 — Output initialization**

The software shall configure the specified GPIO pin as an output and establish its required initial electrical state.

**GPIO_REQ_003 — Input acquisition**

The software shall provide the current logical state of the configured input signal.

**GPIO_REQ_004 — Output control**

The software shall support activating and deactivating the configured output signal.

**GPIO_REQ_005 — Interrupt detection**

The software shall detect configured rising-edge and falling-edge input transitions.

**GPIO_REQ_006 — Debouncing**

The software shall reject input transitions that do not remain stable for the configured debounce interval.

**GPIO_REQ_007 — Active-low handling**

The software shall translate active-low electrical input states into the corresponding logical signal states.

**GPIO_REQ_008 — Error handling**

The software shall report unsupported GPIO configurations during initialization.

Requirements must specify initial state, signal polarity, timing and boundary behavior where applicable.

## 15. Verification and Testing

### Unit testing

Test:

- Configuration validation.
- Input state conversion.
- Active-high/active-low handling.
- Output state conversion.
- Debounce state machine.
- Edge detection.
- Timeout behavior.
- Error propagation.

Use mock GPIO hardware interfaces for hardware-independent testing.

### Integration testing

Test:

- GPIO initialization.
- Input acquisition.
- Output control.
- Interrupt configuration.
- Interrupt event handling.
- Alternate-function configuration.
- Low-power behavior.
- Peripheral interaction.

### Hardware testing

Test:

- Logic HIGH and LOW voltage.
- Output drive capability within specified limits.
- Input voltage thresholds.
- Pull-up and pull-down behavior.
- Rise and fall times.
- Glitch-free initialization.
- Interrupt latency.
- Debounce timing.
- Reset behavior.
- Low-power leakage.
- Pin multiplexing conflicts.

### Boundary testing

Test:

- Invalid pin identifier.
- Unsupported operating mode.
- Unsupported alternate function.
- Unconfigured pin.
- Input transition at debounce boundary.
- Repeated interrupts.
- Simultaneous GPIO events.
- Reset during output activation.
- GPIO access before initialization.
- GPIO access after shutdown.

Never claim physical electrical verification based only on host-based unit tests.

## 16. Performance and Real-Time Analysis

Evaluate:

- GPIO access latency.
- Interrupt response time.
- Interrupt execution time.
- Event processing latency.
- Debounce latency.
- CPU utilization.
- Maximum supported event frequency.
- Event queue capacity.
- Lost-event behavior.

For high-frequency GPIO signals, consider:

- Hardware timer input capture.
- External interrupt hardware.
- Timer encoder mode.
- Dedicated peripheral interfaces.
- DMA, where supported.

Do not use software polling when hardware peripherals provide a more deterministic solution.

## 17. Agent Development Workflow

When implementing GPIO functionality, follow this workflow.

### Step 1: Inspect the project

- Inspect repository structure.
- Identify existing GPIO drivers.
- Identify hardware abstraction interfaces.
- Inspect build system and dependencies.
- Identify coding conventions.
- Identify test infrastructure.

Reuse existing project infrastructure when appropriate.

### Step 2: Analyze requirements

- Identify GPIO pin mapping.
- Identify electrical constraints.
- Identify signal polarity.
- Identify initialization requirements.
- Identify interrupt and timing requirements.
- Identify platform dependencies.
- Identify missing information.

Document assumptions explicitly.

### Step 3: Design

- Define GPIO interfaces.
- Define pin configuration structures.
- Define logical signal abstractions.
- Define error codes.
- Define pin ownership.
- Define interrupt behavior.
- Define test strategy.

### Step 4: Implement

- Implement hardware-independent GPIO services.
- Implement MCU-specific GPIO integration.
- Implement interrupt handling.
- Implement signal processing where required.
- Implement error handling.
- Implement unit tests.

### Step 5: Verify

- Build the project.
- Run unit tests.
- Run static analysis where available.
- Check compiler warnings.
- Validate pin mappings against MCU documentation.
- Identify hardware tests still required.

### Step 6: Review

Perform a senior-level review covering:

- Pin configuration correctness.
- Electrical safety.
- Initialization glitches.
- Signal polarity.
- Interrupt behavior.
- Concurrency.
- Real-time performance.
- Memory safety.
- Portability.
- Test coverage.

### Step 7: Document

Provide:

- GPIO architecture.
- Pin mapping.
- Configuration documentation.
- API documentation.
- Electrical assumptions.
- Interrupt context.
- Verification results.
- Known limitations.
- Integration instructions.

## 18. Expected Agent Deliverables

Depending on task scope, produce:

1. Requirements analysis.
2. GPIO pin mapping.
3. Architecture/design proposal.
4. Configuration definitions.
5. Driver implementation.
6. GPIO service implementation.
7. Unit tests.
8. Integration test specifications.
9. Hardware verification procedures.
10. Build and integration instructions.
11. Verification report.
12. Known limitations and assumptions.

## 19. Senior Engineer Decision Principles

Always prioritize:

- Electrical correctness.
- Hardware documentation over assumptions.
- Deterministic initialization.
- Explicit signal polarity.
- Clear ownership of pins.
- Reliable interrupt processing.
- Non-blocking event handling.
- Appropriate debounce strategy.
- Explicit error handling.
- Testable and portable architecture.
- No unsupported hardware capability claims.
- No fabricated test results.

The objective is to deliver production-quality GPIO software suitable for resource-constrained embedded systems, with predictable electrical behavior, maintainable architecture and verifiable functionality.
