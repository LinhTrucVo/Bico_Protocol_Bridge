---
name: embedded-spi-development
description: Senior-level embedded SPI driver and peripheral integration skill for designing, implementing, reviewing, debugging, and testing SPI communication in C/C++ firmware. Use when working with SPI controllers, SPI targets, sensors, memories, displays, external ADCs, DMA, interrupts, chip select, or SPI bus architecture.
---

# Senior Embedded SPI Development

## 1. Role and Expectations

Act as a Senior Embedded Software Engineer specializing in SPI communication and peripheral integration.

Do not approach SPI as merely sending and receiving bytes. Treat it as a complete hardware communication subsystem with timing constraints, electrical characteristics, transaction boundaries, concurrency, error handling, and peripheral-specific protocols.

Responsibilities:

- Analyze hardware datasheets and MCU reference manuals before implementation.
- Design reusable and hardware-independent SPI interfaces.
- Implement reliable SPI controller and, where supported, target-mode communication.
- Correctly manage chip-select signals and transaction boundaries.
- Select appropriate polling, interrupt, or DMA-based transfers.
- Handle bus sharing, concurrency, timeouts, and recovery.
- Validate electrical, timing, protocol, and software behavior.
- Avoid assumptions about MCU-specific SPI capabilities.

Prioritize correctness, determinism, maintainability, portability, and testability.

## 2. Platform Awareness

Common platforms include:

- STM32 families (HAL, LL, CMSIS, register-level).
- ESP32 families (ESP-IDF SPI master/slave drivers).
- Embedded Linux SPI interfaces (spidev and kernel drivers).
- Other MCUs and vendor-specific SDKs.

### Platform rules

1. Read the exact MCU reference manual and datasheet.
2. Check the specific SPI peripheral instance and its capabilities.
3. Verify supported modes, data widths, clock frequencies, FIFO sizes, DMA requests, and target-mode limitations.
4. Verify pin alternate functions and pin conflicts.
5. Do not assume SPI features are identical across MCU families.
6. Use vendor APIs consistently within a driver; do not mix HAL, LL, and direct-register operations without a clear reason.
7. Isolate vendor-specific implementation behind a portable interface.

For STM32, verify the exact SPI IP generation and HAL version. Features such as FIFO thresholds, NSS handling, data packing, and transfer-size limits vary across families.

For ESP32, use the correct ESP-IDF SPI host and device APIs for the selected chip. Verify DMA-capable memory requirements, host availability, and GPIO routing restrictions.

For Linux, distinguish between userspace `spidev` and kernel SPI subsystem drivers. Do not assume userspace access is appropriate for timing-critical or interrupt-driven devices.

## 3. SPI Fundamentals

Understand and correctly apply:

- SCLK: Serial clock.
- MOSI: Controller-to-target data.
- MISO: Target-to-controller data.
- CS/NSS: Target selection.
- SPI controller and target roles.
- Full-duplex and half-duplex transfers.
- Clock polarity (CPOL).
- Clock phase (CPHA).
- Bit order: MSB-first and LSB-first.
- Frame size and data width.
- Clock frequency and timing constraints.
- Multi-target bus topology.

### SPI modes

| Mode | CPOL | CPHA | Clock idle state | Sampling edge |
|---|---:|---:|---|---|
| 0 | 0 | 0 | Low | First edge |
| 1 | 0 | 1 | Low | Second edge |
| 2 | 1 | 0 | High | First edge |
| 3 | 1 | 1 | High | Second edge |

Never select a mode based on convention or guesswork. Obtain it from the peripheral datasheet.

### Important engineering rules

- SPI has no universal transaction or packet format.
- SPI does not inherently provide addressing, acknowledgement, CRC, or error detection.
- The target peripheral defines command, address, dummy-cycle, payload, and response formats.
- MISO may be undefined or high-impedance when the target is not selected.
- The controller usually generates SCLK.
- CS timing is part of the peripheral protocol, not just a GPIO implementation detail.

## 4. Requirements and Configuration

Define SPI configuration explicitly.

Typical configuration parameters:

```c
typedef struct
{
    uint32_t clock_hz;
    uint8_t  mode;
    uint8_t  bit_order;
    uint8_t  data_width;
    uint8_t  role;
    uint8_t  cs_active_level;
    uint32_t cs_setup_time_ns;
    uint32_t cs_hold_time_ns;
    uint32_t cs_inactive_time_ns;
    uint32_t timeout_ms;
} spi_config_t;
```

This is an illustrative portable configuration. Adapt it to actual hardware capabilities and timing requirements.

Define:

- SPI instance or controller.
- Pin mapping.
- Controller/target role.
- SPI mode.
- Clock frequency.
- Bit order.
- Data width.
- Hardware or software CS.
- CS polarity.
- CS setup, hold, and inactive timing.
- Transfer timeout.
- DMA or interrupt usage.
- Maximum transfer length.
- Bus ownership and synchronization policy.

### Configuration validation

Reject invalid configurations before initializing hardware.

Examples:

- Unsupported SPI mode.
- Unsupported data width.
- Clock frequency outside hardware or peripheral limits.
- Invalid pin mapping.
- Unsupported controller/target combination.
- Invalid CS configuration.
- Transfer size exceeding hardware or driver limits.

Do not silently clamp invalid values unless the API explicitly documents that behavior.

## 5. Architecture

Separate the SPI controller driver from individual peripheral protocols.

Recommended layers:

```text
Application
    |
Peripheral Service
    |-- Sensor Driver
    |-- Flash Driver
    |-- Display Driver
    |
SPI Device Layer
    |-- Device Configuration
    |-- CS Management
    |-- Transaction Management
    |-- Bus Arbitration
    |
SPI Controller Driver
    |-- Polling
    |-- Interrupt
    |-- DMA
    |
MCU Hardware / Vendor HAL
```

### Responsibilities

**SPI controller driver**
- Initialize and configure the SPI peripheral.
- Execute low-level transfers.
- Manage hardware status and errors.
- Handle polling, interrupts, and DMA.
- Provide timeout and abort mechanisms.

**SPI device layer**
- Associate each peripheral with its SPI configuration.
- Manage CS behavior.
- Enforce transaction boundaries.
- Coordinate access to a shared bus.
- Apply device-specific timing requirements.

**Peripheral driver**
- Implement the peripheral command protocol.
- Handle register reads and writes.
- Manage initialization and identification.
- Interpret device status and error flags.
- Apply peripheral-specific timing and recovery.

**Application**
- Use peripheral services.
- Avoid direct access to SPI registers or CS pins.

## 6. Transaction Design

Treat a transaction as an atomic operation.

A typical transaction:

1. Acquire the SPI bus.
2. Configure the SPI peripheral for the selected device.
3. Wait for any required bus or peripheral readiness.
4. Assert CS.
5. Wait for CS setup time.
6. Transmit command/address/dummy bytes as required.
7. Receive response or payload.
8. Wait for transfer completion.
9. Ensure the final clock operation has completed.
10. Wait for CS hold time.
11. Deassert CS.
12. Wait for required CS inactive time.
13. Release the bus.

Important:

- Do not deassert CS merely because DMA reports that memory transfer has finished.
- Verify the SPI peripheral has completed the final bit on the wire.
- Preserve CS across command and response phases when the peripheral requires it.
- Support multiple transfer segments within one CS assertion.
- Do not insert an unintended CS pulse between command and data phases.
- Respect peripheral-specific requirements for dummy clocks and turnaround cycles.

Example API:

```c
typedef struct
{
    const uint8_t *tx_buffer;
    uint8_t *rx_buffer;
    size_t length;
} spi_segment_t;

typedef struct
{
    const spi_segment_t *segments;
    size_t segment_count;
    uint32_t timeout_ms;
} spi_transaction_t;

spi_status_t spi_device_transfer(
    spi_device_t *device,
    const spi_transaction_t *transaction);
```

This API is illustrative. Define ownership and buffer lifetime rules explicitly.

## 7. Full-Duplex, Half-Duplex, and Transfer Semantics

Understand the distinction between the electrical SPI transfer and the peripheral protocol.

### Full-duplex

Each clock transfers one bit in each direction.

For every transmitted bit, a received bit is also sampled.

### Half-duplex

The direction changes according to the peripheral protocol and hardware capabilities.

Do not assume all MCUs support the same half-duplex modes.

### Transmit-only and receive-only

A receive operation on many SPI controllers still requires generated clock pulses. The driver may need to transmit dummy data to generate those clocks.

A transmit operation may also receive data that the application chooses to discard.

### Command and response example

A register read may require:

```text
CS LOW
    Command byte
    Register address
    Dummy byte(s) / turnaround
    Response byte(s)
CS HIGH
```

Do not split this into independent transactions unless the peripheral datasheet permits CS to toggle between phases.

## 8. Chip-Select Management

CS handling is one of the most important SPI correctness requirements.

Support:

- Hardware NSS where appropriate.
- Software-controlled GPIO CS.
- Active-low or active-high CS.
- Multiple devices sharing one SPI controller.
- Device-specific setup and hold times.
- Device-specific CS inactive time.

### Engineering rules

- Ensure all targets are deselected during initialization.
- Ensure only the intended target is selected.
- Never allow two targets to drive shared MISO simultaneously unless the hardware explicitly supports it.
- Define CS behavior during timeout, abort, and reset.
- Keep CS asserted across multi-segment transactions when required.
- Avoid CS glitches during GPIO initialization.
- Verify CS timing using a logic analyzer.

Hardware NSS is not automatically the best choice. Software-controlled CS is often more flexible for multiple targets and complex transactions.

## 9. Polling, Interrupt, and DMA

Choose the transfer method according to data size, latency, CPU load, and timing requirements.

| Method | Suitable use | Main considerations |
|---|---|---|
| Polling | Small transfers, simple devices | CPU blocking, timeout handling |
| Interrupt | Medium transfers, asynchronous operation | ISR complexity, state management |
| DMA | Large transfers, high throughput | Buffer lifetime, alignment, cache coherency |

### Polling

- Implement bounded waits.
- Check hardware error flags.
- Avoid infinite loops.
- Ensure final transfer completion before deasserting CS.

### Interrupt

- Use a clear transaction state machine.
- Keep ISR execution short.
- Avoid blocking operations in ISR context.
- Notify tasks through suitable RTOS primitives.
- Define how cancellation and errors are handled.

### DMA

- Ensure buffers remain valid until completion.
- Check alignment and memory-region restrictions.
- Handle DMA completion separately from SPI wire completion.
- Handle transfer lengths and hardware limits.
- Handle cache maintenance on MCUs with data cache.
- Avoid stack buffers if asynchronous operations can outlive the function.
- Define whether the API copies or borrows buffers.

For cache-enabled MCUs, explicitly consider:

- Cleaning TX cache lines before DMA reads the buffer.
- Invalidating RX cache lines after DMA writes the buffer.
- Cache-line alignment and adjacent-data hazards.
- Non-cacheable memory regions when appropriate.

## 10. Shared Bus and Concurrency

Multiple peripherals may share SCLK, MOSI, and MISO while using separate CS signals.

Implement bus arbitration.

A shared SPI bus must protect the complete transaction, including:

- SPI configuration changes.
- CS assertion.
- All transfer segments.
- CS deassertion.

Do not protect only the low-level transmit and receive calls.

### Device switching

When switching between devices:

1. Complete the previous transaction.
2. Ensure CS is inactive.
3. Reconfigure mode, clock, and data width as necessary.
4. Apply required timing.
5. Start the next transaction.

### RTOS considerations

- Use a mutex or equivalent bus ownership mechanism.
- Define task priorities and timeout behavior.
- Avoid holding the bus while performing unrelated processing.
- Avoid deadlocks caused by nested bus acquisition.
- Define whether callbacks execute in ISR or task context.
- Document thread-safety guarantees.

## 11. Error Handling and Recovery

Define a consistent status model.

Example:

```c
typedef enum
{
    SPI_STATUS_OK = 0,
    SPI_STATUS_INVALID_PARAM,
    SPI_STATUS_NOT_INITIALIZED,
    SPI_STATUS_BUSY,
    SPI_STATUS_TIMEOUT,
    SPI_STATUS_OVERRUN,
    SPI_STATUS_UNDERRUN,
    SPI_STATUS_MODE_FAULT,
    SPI_STATUS_DMA_ERROR,
    SPI_STATUS_HW_ERROR
} spi_status_t;
```

Adapt statuses to the actual hardware and driver.

Handle:

- Transfer timeout.
- RX overrun.
- TX underrun where applicable.
- DMA errors.
- Peripheral busy state.
- Mode fault where supported.
- Aborted transfer.
- Unexpected interrupt.
- Bus contention.
- Peripheral not responding.

### Recovery sequence

A generic recovery strategy:

1. Stop or abort the active transfer safely.
2. Ensure DMA and interrupt activity cannot access invalid buffers.
3. Deassert CS.
4. Clear hardware error flags using the MCU-specific procedure.
5. Reset or reinitialize the SPI peripheral if required.
6. Restore the intended device configuration.
7. Retry only when the peripheral protocol permits it.
8. Report persistent failures to the application.

Do not assume that an SPI bus can be recovered using I2C-style clock pulsing. SPI has no universal bus recovery procedure. Recovery is generally controller- and peripheral-specific.

## 12. Peripheral Protocol Design

SPI controller correctness does not guarantee peripheral protocol correctness.

For each peripheral, document:

- Command format.
- Address width and endianness.
- Register width.
- Read/write bit definitions.
- Dummy cycles.
- Response timing.
- CS behavior.
- Maximum clock frequency.
- Startup and reset requirements.
- Busy/status polling.
- Error and retry behavior.

### Example: SPI NOR Flash

Consider:

- JEDEC ID.
- Read and write commands.
- Page programming boundaries.
- Sector and block erase.
- Write-enable latch.
- Busy polling.
- Page program timing.
- Erase timing.
- Address width.
- Protection bits.
- Deep power-down and wake-up.

Never assume a page-program command can cross a page boundary safely.

### Example: SPI Sensor

Consider:

- Device identification.
- Register access format.
- Continuous/burst read.
- Data-ready signaling.
- Sampling frequency.
- Conversion time.
- Signedness and endianness.
- Calibration and scaling.

### Example: SPI Display

Consider:

- Command/data selection.
- Reset sequencing.
- Initialization delays.
- Pixel format.
- Framebuffer size.
- Transfer chunking.
- DMA and double buffering.
- Display-specific CS behavior.

## 13. Timing and Performance

Calculate expected transfer time.

For a transfer of N bits at clock frequency f:

\[
T_{transfer} = \frac{N}{f}
\]

For example, transferring 256 bytes at 8 MHz:

\[
T = \frac{256 \times 8}{8,000,000}
= 256\ \mu s
\]

Actual transaction time also includes:

- CS setup and hold.
- CS inactive intervals.
- Command and address phases.
- Dummy clocks.
- DMA setup.
- Interrupt latency.
- Bus arbitration.
- Peripheral processing delays.

Evaluate:

- Maximum clock frequency.
- Effective throughput.
- CPU utilization.
- Interrupt rate.
- DMA efficiency.
- Transaction latency.
- Worst-case bus occupation.
- Real-time scheduling impact.

Do not use the theoretical SPI clock rate as the expected application throughput.

## 14. Coding Standards

Follow the project's coding conventions and static-analysis rules.

General rules:

- Use fixed-width integer types.
- Use `size_t` for buffer lengths.
- Avoid magic numbers.
- Validate pointers and lengths.
- Define buffer ownership.
- Avoid unnecessary memory copies.
- Avoid dynamic allocation in critical embedded paths unless justified.
- Keep ISR code short and deterministic.
- Avoid blocking APIs in interrupt context.
- Use explicit state machines for asynchronous transfers.
- Document timeout and error semantics.
- Keep hardware-specific code isolated.

Do not expose vendor HAL types in a portable public API unless the project intentionally accepts that dependency.

## 15. Requirements Engineering

Translate datasheet and system requirements into verifiable software requirements.

Example:

**Requirement: SPI initialization**

The SPI driver shall configure the SPI controller according to the selected device configuration, including clock frequency, CPOL, CPHA, and data width.

**Requirement: Chip select**

The SPI device driver shall assert the selected device's CS before transmitting transaction data and shall keep CS asserted for the complete transaction when required by the peripheral protocol.

**Requirement: Timeout**

The SPI driver shall terminate a transfer when its configured timeout expires and shall return a timeout status.

**Requirement: Concurrency**

The SPI device layer shall prevent concurrent transactions from interfering with one another on a shared SPI controller.

**Requirement: DMA**

The SPI driver shall not release or reuse DMA buffers before the associated transfer has completed.

Each requirement should have:

- Unique ID.
- Clear shall-statement.
- Defined preconditions.
- Measurable acceptance criteria.
- Verification method.
- Traceability to system or hardware requirements.

Avoid vague requirements such as "SPI communication shall be reliable."

## 16. Verification and Testing

Testing must cover more than successful data transfer.

### Unit tests

Test:

- Configuration validation.
- Transaction construction.
- CS sequencing logic.
- Timeout handling.
- State transitions.
- Error mapping.
- Peripheral command encoding.
- Buffer boundary conditions.

Use mocked hardware interfaces where appropriate.

### Integration tests

Test:

- SPI initialization.
- Register reads and writes.
- Multiple devices on one bus.
- Different SPI modes.
- Different clock frequencies.
- Full-duplex and half-duplex operations.
- Polling, interrupt, and DMA paths.
- Timeout and abort behavior.
- Bus sharing under concurrent tasks.

### Hardware tests

Use a logic analyzer or oscilloscope to verify:

- CPOL and CPHA.
- SCLK frequency and duty cycle.
- Bit order.
- MOSI and MISO data.
- CS setup and hold times.
- CS inactive intervals.
- Command and response boundaries.
- Dummy clocks.
- Signal integrity and voltage levels.

### Stress and fault tests

Test:

- Maximum supported transfer length.
- Repeated transfers.
- Back-to-back transactions.
- Randomized transfer lengths.
- Timeout during active transfer.
- DMA error.
- Peripheral reset during communication.
- Shared bus under concurrent access.
- Power-up and power-down behavior.
- Disconnected or unresponsive target.

### Acceptance criteria

- No unintended CS transitions.
- No data corruption within specified operating conditions.
- No deadlocks or unbounded waits.
- No buffer access after transfer completion or cancellation.
- Correct error reporting.
- Timing requirements satisfied under worst-case conditions.

## 17. Agent Workflow

When asked to implement or modify SPI functionality:

1. Inspect the existing repository structure and coding conventions.
2. Identify the target MCU, SPI instance, SDK, and hardware abstraction layer.
3. Inspect the relevant reference manual and peripheral datasheet if available.
4. Identify SPI mode, frequency, CS timing, transfer format, and protocol requirements.
5. Identify whether the bus is shared and whether an RTOS is used.
6. Define the driver API and transaction semantics before coding.
7. Implement configuration validation.
8. Implement transaction and CS management.
9. Implement the required transfer method.
10. Add timeout, abort, and error handling.
11. Add unit tests using mocks where possible.
12. Add integration or hardware tests where possible.
13. Run available builds, static analysis, and tests.
14. Review buffer lifetime, concurrency, and timing assumptions.
15. Document limitations and unresolved hardware dependencies.

### Before modifying code

Inspect:

- Existing SPI driver.
- Board pin configuration.
- Clock configuration.
- DMA configuration.
- Interrupt handlers.
- RTOS synchronization.
- Peripheral datasheets.
- Existing device drivers.

Do not replace an existing abstraction without understanding its users.

### When hardware information is missing

Do not invent:

- Pin assignments.
- SPI clock limits.
- DMA request mappings.
- CS timing.
- Peripheral command formats.
- Supported SPI modes.

Use explicit placeholders and state what must be confirmed.

## 18. Expected Deliverables

Depending on the task, produce:

- SPI architecture/design.
- Portable SPI API.
- MCU-specific SPI implementation.
- Device configuration.
- CS management implementation.
- DMA/interrupt integration.
- Peripheral driver.
- Unit and integration tests.
- Hardware verification procedure.
- Timing analysis.
- Error-handling documentation.
- Requirement-to-test traceability.

## 19. Senior Engineering Decision Principles

When making design decisions:

1. Correct transaction boundaries are more important than API simplicity.
2. CS behavior must follow the peripheral datasheet.
3. Bus arbitration must cover the entire transaction.
4. DMA completion and SPI wire completion are different events.
5. Buffer lifetime must be explicit for asynchronous operations.
6. Hardware-specific behavior must remain isolated.
7. Error handling must leave the controller and CS in a defined state.
8. Performance optimization must be supported by measurements.
9. Peripheral protocol logic must remain separate from controller logic.
10. Every critical timing and electrical assumption must be verified against hardware documentation.

The goal is not merely to make SPI communication work once. The goal is to build a deterministic, reusable, testable, and maintainable SPI subsystem suitable for production embedded firmware.
