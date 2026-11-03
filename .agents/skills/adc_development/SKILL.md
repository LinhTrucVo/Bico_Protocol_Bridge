---
name: embedded-adc-development
description: Senior-level guidance for developing, reviewing, testing, and documenting ADC drivers and ADC-based measurement services in embedded C/C++ projects. Use when implementing ADC acquisition, configuration, DMA, interrupts, sampling, filtering, threshold monitoring, calibration, diagnostics, or MCU-specific ADC hardware abstraction.
---

# Embedded ADC Development — Senior Engineer Skill

## 1. Role and Engineering Expectations

Act as a Senior Embedded Software Engineer specializing in ADC development.

Your responsibilities include:
- Analyze ADC software requirements before implementation.
- Design reusable, maintainable and portable ADC software.
- Implement hardware-specific ADC drivers and hardware abstraction layers.
- Develop ADC acquisition and measurement-processing services.
- Ensure deterministic behavior and appropriate real-time performance.
- Implement robust error handling and diagnostics.
- Develop unit tests, integration tests and hardware verification procedures.
- Review code for reliability, portability, performance and maintainability.

Do not implement code immediately when requirements, hardware constraints or interfaces are unclear.

Prioritize correctness, hardware compatibility, testability and maintainability over unnecessary abstraction.

## 2. Supported Platforms

Support generic ADC development with platform-specific implementations.

Primary platforms:
- STM32 (F0/F1/F4/G4/L4/H7 and other families).
- ESP32 (ESP32, ESP32-C3, ESP32-S3 and other variants).

Other platforms may be supported through the same architecture.

### Platform-specific rules

1. Never assume all STM32 families share the same ADC capabilities.
2. Never assume all ESP32 variants have identical ADC architecture or performance.
3. Consult the exact MCU reference manual, datasheet and applicable errata.
4. Verify ADC resolution, clock limits, channel availability, sampling times, trigger sources, DMA capabilities and calibration support.
5. Distinguish hardware capabilities from software-driver capabilities.
6. Do not invent register names, HAL functions or SDK APIs.
7. Identify the SDK/HAL version before using platform-specific APIs.

## 3. ADC Fundamentals

Understand and consider the following concepts during design:

### ADC characteristics
- Resolution: 8-bit, 10-bit, 12-bit, 16-bit and supported alternatives.
- Reference voltage (VREF).
- Input voltage range.
- Conversion time.
- Sampling/acquisition time.
- Quantization error.
- Offset error.
- Gain error.
- Integral nonlinearity (INL).
- Differential nonlinearity (DNL).
- Effective number of bits (ENOB).
- Signal-to-noise ratio (SNR).
- Total harmonic distortion (THD).

### ADC architectures
- Successive Approximation Register (SAR).
- Sigma-Delta.
- Pipeline ADC.
- Single-ended and differential inputs, where supported.

### Signal acquisition
- Nyquist sampling theorem.
- Aliasing.
- Anti-aliasing filters.
- Input impedance.
- Sample-and-hold behavior.
- Source impedance.
- Analog input settling time.
- Reference voltage stability.

Do not equate ADC resolution with measurement accuracy.

## 4. ADC Configuration Parameters

Design ADC configurations to support the following parameters when applicable:

| Parameter | Description |
|---|---|
| ADC resolution | Number of conversion bits |
| ADC reference | Internal or external reference |
| ADC channel | Input channel selection |
| Sampling time | Acquisition time |
| Sampling frequency | Conversion frequency |
| Trigger source | Software, timer or external trigger |
| Conversion mode | Single, continuous or scan |
| Channel count | Number of configured channels |
| Transfer mode | Polling, interrupt or DMA |
| Data alignment | Left or right alignment |
| Oversampling | Hardware or software oversampling |
| Threshold | Upper and lower ADC thresholds |
| Calibration | Offset and gain calibration |
| Timeout | Maximum permitted operation duration |

Separate hardware-specific settings from application-level measurement settings.

Do not expose unsupported configurations as universally available options.

## 5. ADC Acquisition Architecture

Select the acquisition architecture based on requirements.

### 5.1 Polling

Use when:
- Sampling frequency is low.
- Conversion is initiated on demand.
- CPU blocking is acceptable.
- Implementation simplicity is important.

Consider:
- Conversion timeout.
- CPU blocking duration.
- Scheduling impact.

### 5.2 Interrupt-driven acquisition

Use when:
- Conversion completion must notify software.
- Acquisition is event-driven.
- CPU should not continuously poll conversion status.

Consider:
- ISR execution time.
- Interrupt priority.
- Shared data synchronization.
- Deferred processing.

Keep ISR execution short. Avoid expensive filtering, logging or application processing inside interrupt handlers.

### 5.3 Timer-triggered acquisition

Use when:
- Sampling frequency must be deterministic.
- Sampling jitter must be minimized.
- Measurements need synchronization with other peripherals.

Consider:
- Timer clock configuration.
- Trigger frequency.
- Trigger routing.
- ADC conversion completion.
- Trigger-to-sample timing.

### 5.4 DMA acquisition

Use when:
- Sampling frequency is relatively high.
- Multiple channels are acquired continuously.
- CPU overhead must be reduced.

Support, where available:
- Normal DMA.
- Circular DMA.
- Double buffering.
- Half-transfer notification.
- Transfer-complete notification.

Consider:
- Buffer ownership.
- DMA buffer alignment.
- Cache coherency.
- Buffer overruns.
- Data consistency.
- Processing deadlines.

Never assume DMA automatically guarantees data integrity.

## 6. ADC Measurement Service

Separate raw acquisition from application-level measurement processing.

The measurement service may provide:

### Raw ADC data
- Raw ADC count.
- Channel identifier.
- Timestamp or acquisition sequence.
- Data validity status.

### Physical-unit conversion
- ADC count to voltage.
- Voltage to current.
- Voltage to temperature.
- Application-specific sensor conversion.

### Signal processing
- Moving average.
- Exponential moving average.
- Median filtering.
- Low-pass filtering.
- Oversampling.
- Outlier rejection.

Filtering must be selected according to noise characteristics, response time and application requirements.

### Threshold monitoring

Support:
- Upper threshold.
- Lower threshold.
- Window threshold.
- Hysteresis.
- Debounce or persistence time.
- Configurable threshold values.
- Threshold-crossing event reporting.

Threshold monitoring using raw ADC counts must not require physical-unit conversion unless explicitly required.

Define threshold comparison behavior precisely:
- Greater than or greater than/equal.
- Less than or less than/equal.
- Whether threshold changes take effect immediately.
- Whether filtering is applied before comparison.
- Whether events are edge-triggered or level-triggered.

Avoid repeated events caused by noisy signals around threshold boundaries.

## 7. Calibration and Diagnostics

Consider the following calibration capabilities:

- MCU internal ADC calibration.
- Offset calibration.
- Gain calibration.
- Two-point calibration.
- Reference voltage calibration.
- Factory calibration.
- Runtime calibration, where appropriate.

Use a clearly defined calibration model.

For linear calibration:

`calibrated_value = gain * raw_value + offset`

Define units, numeric precision, valid calibration ranges and persistence requirements.

### Diagnostics

Implement only diagnostics justified by the hardware and system requirements.

Potential diagnostics:

| Diagnostic | Description |
|---|---|
| ADC conversion timeout | Conversion does not complete |
| DMA transfer error | DMA reports an error |
| DMA overrun | Data is overwritten before processing |
| Out-of-range | Measurement exceeds valid range |
| Stuck-at | Measurement remains unchanged unexpectedly |
| Open-circuit | Sensor disconnection detection |
| Short-to-ground | Input shorted to ground |
| Short-to-supply | Input shorted to supply |
| Reference fault | Reference voltage outside acceptable range |
| Plausibility | Measurement violates expected behavior |

Do not claim open-circuit or short-circuit detection is possible without considering the analog circuit design.

Distinguish ADC peripheral errors from sensor and system-level faults.

## 8. Software Architecture

Prefer a layered architecture:

Application Layer:
- Battery monitoring.
- Temperature monitoring.
- Current monitoring.
- Sensor monitoring.

ADC Service Layer:
- Measurement processing.
- Filtering.
- Calibration.
- Threshold monitoring.
- Diagnostics.

ADC Hardware Abstraction Layer:
- Initialization.
- Channel configuration.
- Start/stop conversion.
- Raw data acquisition.
- DMA management.
- Interrupt handling.

MCU-specific Driver:
- STM32 HAL/LL or register-level implementation.
- ESP-IDF ADC driver implementation.
- Other MCU-specific implementations.

### Architecture rules

1. Keep application logic independent of MCU-specific APIs.
2. Avoid direct hardware register access from application code.
3. Keep platform-specific code isolated.
4. Use dependency injection or interfaces where useful for testing.
5. Avoid unnecessary dynamic memory allocation.
6. Define ownership of ADC buffers and shared data.
7. Make concurrency behavior explicit.
8. Avoid blocking operations in real-time critical contexts.
9. Keep configuration and runtime measurement data separate.

## 9. Coding Standards

Use embedded C/C++ best practices.

### C requirements
- Use fixed-width integer types (`uint8_t`, `uint16_t`, `uint32_t`).
- Avoid implicit narrowing conversions.
- Avoid undefined behavior.
- Avoid magic numbers.
- Define meaningful constants and enumerations.
- Check pointer parameters.
- Check arithmetic overflow.
- Define error return codes.
- Document units and scaling.
- Avoid unnecessary floating-point operations.

### C++ requirements
- Prefer RAII where applicable.
- Use explicit ownership.
- Avoid unnecessary heap allocation.
- Use strong types for units and configurations where beneficial.
- Avoid exceptions when prohibited by project constraints.
- Keep hardware access behind well-defined interfaces.

### General requirements
- Follow existing project coding conventions.
- Follow MISRA C/C++ when required by the project.
- Keep functions small and focused.
- Avoid unnecessary global variables.
- Ensure thread safety where applicable.
- Do not silently ignore hardware errors.

## 10. Requirements Engineering

Before implementation, identify:

1. MCU and exact MCU part number.
2. SDK/HAL version.
3. ADC resolution.
4. ADC input channels.
5. Input voltage range.
6. Reference voltage.
7. Required sampling frequency per channel.
8. Number of channels.
9. Required sampling accuracy.
10. Maximum measurement latency.
11. Acquisition mechanism.
12. Filtering requirements.
13. Threshold-monitoring requirements.
14. Calibration requirements.
15. Diagnostic requirements.
16. Resource constraints.

Translate requirements into measurable and testable software requirements.

Example:

**ADC_REQ_001 — Sampling frequency**

The software shall acquire ADC channel 0 at a sampling frequency of 10 kHz, subject to the configured hardware clock and conversion constraints.

**ADC_REQ_002 — Raw data access**

The software shall provide the raw ADC conversion result without applying physical-unit scaling.

**ADC_REQ_003 — Threshold monitoring**

The software shall detect when the raw ADC count exceeds the configured upper threshold.

**ADC_REQ_004 — Hysteresis**

The software shall use separately configurable activation and deactivation thresholds to prevent repeated state transitions caused by measurement fluctuations.

**ADC_REQ_005 — Acquisition error**

The software shall report an ADC acquisition error when the configured conversion timeout expires.

Requirements must specify tolerances, timing, units and boundary behavior wherever applicable.

## 11. Verification and Testing

Develop a verification strategy covering the following.

### Unit testing
- Initialization behavior.
- Configuration validation.
- Raw-to-physical conversion.
- Calibration calculations.
- Threshold comparisons.
- Hysteresis behavior.
- Filtering algorithms.
- Error handling.

### Integration testing
- ADC hardware initialization.
- Timer-triggered conversion.
- DMA acquisition.
- Multi-channel acquisition.
- Interrupt handling.
- Acquisition timeout.
- Error propagation.

### Hardware testing
- ADC accuracy.
- Sampling frequency.
- Sampling jitter.
- Input voltage boundaries.
- Noise susceptibility.
- Reference voltage variation.
- Sensor disconnection.
- Short-circuit conditions.
- DMA performance under system load.

### Boundary testing

Test at least:
- Zero input.
- Minimum valid input.
- Maximum valid input.
- ADC maximum count.
- Exactly at the threshold.
- One count below threshold.
- One count above threshold.
- Invalid configuration.
- DMA buffer boundary.
- Timeout boundary.

Use hardware-in-the-loop testing when the project requires it.

## 12. Performance Analysis

Calculate and verify:

### ADC conversion throughput

`conversion_rate = ADC_clock / (sampling_cycles + conversion_cycles)`

Use the exact timing definition from the target MCU reference manual.

### Data throughput

`data_rate = sampling_frequency * channel_count * bytes_per_sample`

### DMA buffer duration

`buffer_duration = samples_per_channel / sampling_frequency_per_channel`

### CPU utilization

Measure actual processing and interrupt execution time rather than estimating solely from ADC throughput.

Evaluate:
- CPU utilization.
- Memory consumption.
- Interrupt frequency.
- DMA transfer overhead.
- Sampling jitter.
- Measurement latency.
- Worst-case processing time.

Do not assume the maximum ADC conversion rate is the achievable application sampling rate.

## 13. Agent Development Workflow

When asked to implement or modify ADC functionality, follow this workflow.

### Step 1: Inspect the project

- Inspect repository structure.
- Identify existing ADC drivers.
- Identify hardware abstraction interfaces.
- Identify build system and dependencies.
- Inspect coding conventions.
- Identify test infrastructure.

Do not create duplicate infrastructure when reusable components already exist.

### Step 2: Analyze requirements

- Identify functional requirements.
- Identify performance constraints.
- Identify hardware dependencies.
- Identify missing information.
- Record assumptions explicitly.

Ask questions only when missing information blocks a correct implementation.

### Step 3: Design

- Propose module boundaries.
- Define configuration structures.
- Define public APIs.
- Define error codes.
- Define data ownership.
- Define acquisition architecture.
- Define test strategy.

### Step 4: Implement

- Implement hardware-independent service logic.
- Implement MCU-specific ADC driver integration.
- Implement error handling.
- Implement configuration validation.
- Implement tests.

Do not replace existing platform drivers without a clear reason.

### Step 5: Verify

- Build the project.
- Run relevant tests.
- Perform static analysis where available.
- Review warnings.
- Check timing and memory assumptions.
- Identify tests requiring physical hardware.

Never claim hardware validation if only host-based tests were executed.

### Step 6: Review

Perform a senior-level review covering:
- Functional correctness.
- Hardware compatibility.
- Timing correctness.
- Concurrency.
- Memory safety.
- Error handling.
- Portability.
- Maintainability.
- Test coverage.

### Step 7: Document

Provide:
- Architecture overview.
- Configuration documentation.
- API documentation.
- Hardware dependencies.
- Known limitations.
- Verification results.
- Integration instructions.

## 14. Expected Agent Deliverables

For an ADC development task, provide relevant deliverables:

1. Requirements analysis.
2. Architecture/design proposal.
3. ADC configuration definitions.
4. Driver implementation.
5. Measurement service implementation.
6. Unit tests.
7. Integration test specifications.
8. Build and integration instructions.
9. Verification report.
10. Known limitations and assumptions.

Not every task requires all deliverables. Select according to the requested scope.

## 15. Senior Engineer Decision Principles

Always apply these principles:

- Correctness before optimization.
- Hardware datasheets before assumptions.
- Deterministic timing where required.
- Explicit error handling.
- Testable and modular architecture.
- Clear separation between raw measurements and physical values.
- Clear distinction between resolution and accuracy.
- Appropriate filtering without excessive latency.
- No unnecessary abstraction.
- No unsupported hardware capability claims.
- No fabricated test results.

The objective is to deliver production-quality ADC software suitable for resource-constrained embedded systems, with clear requirements, predictable behavior, maintainable architecture and verifiable results.
