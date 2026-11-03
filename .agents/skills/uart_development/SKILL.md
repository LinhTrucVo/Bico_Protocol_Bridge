---
name: embedded-uart-development
description: Senior-level embedded UART driver and communication development skill for designing, implementing, reviewing, debugging, and testing UART communication in C/C++ firmware. Use when working with UART, USART, serial protocols, interrupt/DMA transfers, ring buffers, RS-232, RS-485, console interfaces, bootloaders, or external serial devices.
---

# Senior Embedded UART Development

## 1. Role and Expectations

Act as a Senior Embedded Software Engineer specializing in UART communication and serial interface development.

Treat UART as a complete communication subsystem rather than a simple byte-transmission peripheral.

Responsibilities:

- Analyze MCU reference manuals, datasheets, and external device specifications.
- Design portable and reusable UART interfaces.
- Implement polling, interrupt-driven, and DMA-driven communication.
- Design reliable asynchronous RX and TX mechanisms.
- Implement ring buffers and message parsing.
- Handle framing, parity, overrun, noise, and other hardware errors.
- Support hardware and software flow control.
- Support RS-232, RS-485, and other UART-based physical interfaces where required.
- Design concurrency-safe APIs for RTOS and bare-metal systems.
- Validate throughput, latency, timing, and signal integrity.
- Provide deterministic timeout and recovery behavior.

Prioritize correctness, robustness, portability, maintainability, and testability.

## 2. Platform Awareness

Common platforms include:

- STM32 families using HAL, LL, CMSIS, or register-level drivers.
- ESP32 families using ESP-IDF UART drivers.
- Embedded Linux serial interfaces using TTY/termios.
- Other MCUs and vendor-specific SDKs.

### Platform rules

1. Identify the exact MCU and UART/USART instance.
2. Check the reference manual for FIFO, DMA, interrupt, and error-handling capabilities.
3. Verify pin alternate functions and pin conflicts.
4. Check whether the peripheral supports synchronous mode, LIN, IrDA, or other USART-specific features if relevant.
5. Verify DMA request mappings and channel limitations.
6. Verify clock configuration and baud-rate generation accuracy.
7. Do not assume UART capabilities are identical across MCU families.
8. Keep vendor-specific code behind a portable interface.

For STM32, check the exact UART IP version, FIFO support, DMA behavior, IDLE detection, receiver timeout, and interrupt flag-clearing sequence.

For ESP32, use the correct ESP-IDF UART driver and verify RX buffer behavior, event queues, FIFO configuration, and pin routing.

For Linux, distinguish between UART hardware configuration, TTY buffering, and application-level framing. Configure termios explicitly rather than relying on terminal defaults.

## 3. UART Fundamentals

Understand:

- TX: Transmit data.
- RX: Receive data.
- GND: Common signal reference.
- Baud rate.
- Data bits.
- Parity.
- Stop bits.
- Frame format.
- Full-duplex communication.
- Hardware and software flow control.
- UART clock and baud-rate error.
- Electrical interface versus logical UART signaling.

### Typical frame format

```text
Idle | Start | Data bits | Parity (optional) | Stop bit(s) | Idle
```

Typical configuration:

```text
115200 baud
8 data bits
No parity
1 stop bit
No flow control
```

Often written as `115200 8N1`.

### Important engineering rules

- UART is asynchronous; transmitter and receiver do not share a clock signal.
- Both sides must use compatible baud rates and frame formats.
- UART logic levels do not define the electrical interface.
- Standard MCU UART pins usually use CMOS/TTL logic levels.
- RS-232 and RS-485 require appropriate transceivers.
- UART does not inherently provide message boundaries, addressing, CRC, or retransmission.
- Application protocols must define framing and error detection where required.

## 4. Configuration and Requirements

Define UART configuration explicitly.

Example:

```c
typedef enum
{
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} uart_parity_t;

typedef enum
{
    UART_STOP_BITS_1 = 0,
    UART_STOP_BITS_2
} uart_stop_bits_t;

typedef enum
{
    UART_FLOW_NONE = 0,
    UART_FLOW_RTS_CTS,
    UART_FLOW_XON_XOFF
} uart_flow_control_t;

typedef struct
{
    uint32_t baud_rate;
    uint8_t data_bits;
    uart_parity_t parity;
    uart_stop_bits_t stop_bits;
    uart_flow_control_t flow_control;
    uint32_t rx_timeout_ms;
    uint32_t tx_timeout_ms;
} uart_config_t;
```

This is an illustrative portable configuration. Adapt it to the selected MCU and driver.

Define:

- UART instance.
- TX/RX pin mapping.
- Baud rate.
- Data width.
- Parity.
- Stop bits.
- Flow-control mode.
- FIFO threshold where supported.
- RX and TX buffer sizes.
- Interrupt priority.
- DMA configuration.
- Timeout behavior.
- Maximum supported transfer length.
- Power-management requirements.

### Configuration validation

Reject unsupported or invalid configurations before enabling the peripheral.

Examples:

- Unsupported baud rate.
- Unsupported data width.
- Invalid parity or stop-bit combination.
- Unsupported flow-control mode.
- Invalid pin assignment.
- Invalid DMA configuration.
- Buffer size outside supported limits.

Do not silently change requested settings unless the API documents the behavior.

## 5. Architecture

Separate UART hardware access from buffering, framing, and application protocols.

Recommended architecture:

```text
Application
    |
Application Protocol
    |-- Command Parser
    |-- Packet Encoder/Decoder
    |-- CRC / Validation
    |
UART Communication Service
    |-- RX Ring Buffer
    |-- TX Queue
    |-- Framing
    |-- Timeout Handling
    |
UART Driver
    |-- Polling
    |-- Interrupt
    |-- DMA
    |-- Error Handling
    |
MCU Hardware / Vendor HAL
    |
UART Pins / Transceiver
```

### Responsibilities

**UART driver**
- Configure hardware.
- Transmit and receive data.
- Manage interrupts and DMA.
- Report hardware errors.
- Implement timeout and abort behavior.

**UART communication service**
- Manage RX and TX buffers.
- Coordinate asynchronous transfers.
- Provide thread-safe communication APIs.
- Detect communication events.
- Manage buffering and overflow policies.

**Protocol layer**
- Define packet boundaries.
- Parse commands and responses.
- Validate lengths and CRC.
- Handle sequence numbers and retransmission if required.

**Application**
- Consume validated messages.
- Avoid direct hardware register access.

Do not mix hardware UART logic with application-specific packet parsing.

## 6. Baud Rate and Timing Analysis

UART baud rate represents the nominal number of signaling symbols per second. For conventional binary UART, each symbol represents one bit.

The actual bit period is:

\[
T_{bit} = \frac{1}{baud\ rate}
\]

For example, at 115200 baud:

\[
T_{bit} \approx 8.68\ \mu s
\]

For a conventional 8N1 frame:

- 1 start bit.
- 8 data bits.
- 1 stop bit.

Total: 10 bits per byte.

The ideal maximum payload rate is:

\[
Throughput = \frac{baud\ rate}{bits\ per\ frame}
\]

At 115200 baud with 8N1:

\[
Throughput = \frac{115200}{10}
= 11520\ bytes/s
\]

Actual throughput may be lower due to protocol overhead, flow control, processing, and idle periods.

### Baud-rate accuracy

Consider:

- MCU peripheral clock accuracy.
- Baud-rate divider quantization.
- Oversampling configuration.
- Receiver clock tolerance.
- External device tolerance.
- Cable and signal integrity effects.

Do not assume that configuring both sides to the same nominal baud rate guarantees reliable communication.

Verify the total transmitter/receiver timing mismatch against the selected MCU and device specifications.

## 7. RX Data Acquisition

Choose an RX strategy based on throughput, latency, memory, and processing requirements.

### Polling

Suitable for:

- Simple boot-time communication.
- Low-rate devices.
- Short blocking operations.
- Debug or diagnostic interfaces.

Requirements:

- Use bounded waits.
- Check hardware errors.
- Avoid infinite loops.
- Define behavior when no data arrives.

### Interrupt-driven RX

Suitable for:

- Asynchronous data arrival.
- Low-to-medium data rates.
- Systems requiring prompt byte handling.

Requirements:

- Keep ISR execution short.
- Avoid blocking calls in ISR context.
- Store received data in a bounded buffer.
- Handle hardware overrun.
- Define buffer overflow behavior.
- Notify application tasks using suitable RTOS primitives.

### DMA-driven RX

Suitable for:

- Continuous data streams.
- Higher baud rates.
- Reduced CPU overhead.
- Large data transfers.

Possible approaches:

- Fixed-length DMA.
- Circular DMA.
- Double-buffer DMA.
- Receive-to-idle DMA where supported.
- DMA plus UART IDLE-line detection.

Important:

- DMA completion does not necessarily indicate a complete application message.
- IDLE detection is a timing event, not a universal packet boundary.
- Circular DMA requires careful producer-position tracking.
- Handle DMA wraparound correctly.
- Do not assume an interrupt occurs exactly once per application packet.
- Protect against data loss while processing DMA buffers.

### RX architecture recommendation

For continuous asynchronous communication, prefer a bounded circular DMA buffer or interrupt-driven ring buffer when supported by the hardware and justified by the data rate.

Separate data acquisition from packet parsing.

## 8. Ring Buffer Design

Ring buffers are commonly used to decouple UART reception from application processing.

Example:

```c
typedef struct
{
    uint8_t *buffer;
    size_t capacity;

    volatile size_t head;
    volatile size_t tail;
} uart_ring_buffer_t;
```

This is a simplified illustration, not a universally thread-safe implementation.

### Design considerations

- Define whether the buffer uses one empty slot to distinguish full from empty.
- Define whether capacity represents usable bytes or allocated bytes.
- Handle index wraparound.
- Avoid overwriting unread data.
- Define overflow policy.
- Define producer and consumer ownership.
- Consider atomic operations or critical sections.
- Ensure memory ordering where required.
- Avoid assuming `volatile` alone provides thread safety.

### Overflow policies

Choose and document one:

- Drop newest data.
- Drop oldest data.
- Stop reception.
- Apply hardware flow control.
- Report overflow and recover.
- Use a protocol-specific resynchronization mechanism.

Do not silently discard data without reporting it when the application requires reliable communication.

## 9. TX Data Transmission

Support synchronous and asynchronous TX APIs where appropriate.

Example:

```c
uart_status_t uart_write(
    uart_handle_t *handle,
    const uint8_t *data,
    size_t length,
    uint32_t timeout_ms);

uart_status_t uart_write_async(
    uart_handle_t *handle,
    const uint8_t *data,
    size_t length);
```

For asynchronous transmission, define:

- Buffer ownership.
- Buffer lifetime.
- Completion notification.
- Cancellation behavior.
- Error reporting.
- Queueing behavior.
- Whether multiple callers can submit data concurrently.

### TX requirements

- Prevent concurrent callers from corrupting the transmit stream.
- Ensure messages are not interleaved unexpectedly.
- Handle partial transfers.
- Distinguish TX data-register empty from transmission complete.
- Do not release a DMA buffer before DMA completion.
- For half-duplex interfaces, wait until the final stop bit has left the transmitter before changing direction.

## 10. Interrupt and DMA Handling

### Interrupt handling

- Identify all relevant interrupt sources.
- Handle RX, TX, and error interrupts independently where appropriate.
- Clear flags using the MCU-specific procedure.
- Avoid lengthy processing in ISR context.
- Do not call blocking RTOS APIs from an ISR.
- Handle unexpected interrupts safely.

### DMA handling

- Verify DMA request mapping.
- Verify buffer alignment and accessible memory regions.
- Handle transfer-size restrictions.
- Define buffer lifetime.
- Handle completion, half-transfer, and error events.
- Consider cache coherency on cache-enabled MCUs.
- Prevent DMA from writing into memory while the application is modifying it.

For cache-enabled MCUs, consider:

- Invalidating RX cache lines before CPU reads DMA-written data.
- Cleaning TX cache lines before DMA reads CPU-written data.
- Cache-line alignment.
- Adjacent-data corruption risks.
- Non-cacheable DMA memory where appropriate.

### Circular DMA

A circular DMA RX buffer is useful for continuous reception.

However:

- Track the DMA write position correctly.
- Handle wraparound.
- Prevent producer/consumer races.
- Process data before unread data is overwritten.
- Use hardware-supported IDLE or timeout events only as acquisition hints.
- Do not treat IDLE as a guaranteed packet delimiter.

## 11. Protocol Framing and Parsing

UART provides a byte stream, not packets.

The protocol layer must identify message boundaries.

Common framing methods:

### Fixed-length packets

Useful when every message has a known fixed size.

### Length-prefixed packets

Example:

```text
[HEADER][LENGTH][PAYLOAD][CRC]
```

Validate the length before accessing payload memory.

### Delimiter-based packets

Example:

```text
START ... PAYLOAD ... END
```

Define escaping rules if payload data may contain delimiter bytes.

### COBS or SLIP

Useful when a delimiter-based framing scheme is required and payload transparency matters.

### Parser requirements

- Support fragmented messages.
- Support multiple messages in one RX buffer.
- Validate packet length.
- Validate header and message type.
- Validate CRC/checksum where required.
- Reject malformed frames.
- Avoid out-of-bounds memory access.
- Handle parser resynchronization.
- Define maximum packet size.
- Avoid unbounded parsing loops.
- Handle buffer overflow and incomplete frames.

Do not assume one UART receive callback equals one complete packet.

## 12. Flow Control

### Hardware flow control

RTS/CTS is used to control transmission according to receiver readiness.

Verify:

- Signal direction.
- Active polarity.
- Pin assignment.
- Hardware support.
- FIFO threshold behavior.
- External device behavior.

Do not confuse UART peripheral RTS/CTS support with automatic flow-control behavior in every MCU implementation.

### Software flow control

XON/XOFF uses control characters in the data stream.

Consider:

- Escaping or binary transparency.
- Protocol compatibility.
- Interaction with arbitrary binary payloads.
- Whether the peripheral supports software flow control.

### Flow-control design

Flow control must prevent RX overflow under the expected worst-case processing delay.

Calculate buffer capacity using:

\[
Buffer\ Size \ge Data\ Rate \times Maximum\ Processing\ Delay
\]

Add margin for scheduling jitter, interrupt latency, and protocol overhead.

If the receiver cannot stop the sender immediately, include bytes already in flight in the buffer calculation.

## 13. RS-232 and RS-485 Integration

UART is a logical communication peripheral. RS-232 and RS-485 define different electrical interfaces.

### RS-232

Consider:

- Dedicated line transceiver.
- Voltage levels and polarity inversion.
- Maximum cable length and data rate.
- Connector and pinout.
- Signal ground.
- ESD protection.

Never connect standard RS-232 voltage levels directly to MCU UART pins.

### RS-485

Consider:

- Differential transceiver.
- Half-duplex or full-duplex topology.
- Driver-enable control.
- Receiver-enable control.
- Bus termination.
- Biasing.
- Node count and loading.
- Bus direction timing.
- Collision avoidance.
- Protocol-level addressing and arbitration.

### Half-duplex RS-485

Typical transmit sequence:

1. Acquire bus ownership.
2. Enable the transmitter.
3. Wait for transceiver enable time if required.
4. Start UART transmission.
5. Wait for UART transmission complete, not merely TX FIFO empty.
6. Disable the transmitter or switch to receive mode.
7. Allow the receiver to settle.
8. Release bus ownership.

Do not switch the transceiver direction immediately after DMA completion. The final UART stop bit may still be transmitting.

## 14. Error Handling and Recovery

Define a consistent status model.

Example:

```c
typedef enum
{
    UART_STATUS_OK = 0,
    UART_STATUS_INVALID_PARAM,
    UART_STATUS_NOT_INITIALIZED,
    UART_STATUS_BUSY,
    UART_STATUS_TIMEOUT,
    UART_STATUS_OVERRUN,
    UART_STATUS_FRAMING_ERROR,
    UART_STATUS_PARITY_ERROR,
    UART_STATUS_NOISE_ERROR,
    UART_STATUS_DMA_ERROR,
    UART_STATUS_BUFFER_OVERFLOW,
    UART_STATUS_ABORTED,
    UART_STATUS_HW_ERROR
} uart_status_t;
```

Adapt the status model to the actual MCU and driver.

### Hardware errors

Handle:

- Overrun error.
- Framing error.
- Parity error.
- Noise error.
- Break detection.
- DMA transfer error.
- FIFO overflow.
- Unexpected peripheral state.

### Software errors

Handle:

- RX buffer overflow.
- TX queue overflow.
- Invalid packet length.
- CRC failure.
- Parser timeout.
- Incomplete frame.
- Unexpected message type.
- Communication timeout.

### Recovery strategy

A generic recovery sequence:

1. Identify the error source.
2. Stop or abort active DMA/interrupt operations safely.
3. Preserve or discard buffered data according to the documented policy.
4. Clear hardware error flags using the MCU-specific procedure.
5. Restore the UART receiver/transmitter state.
6. Reinitialize DMA if necessary.
7. Reset the protocol parser if synchronization is lost.
8. Report the error through diagnostics.
9. Resume reception only when the driver is in a defined state.

Do not silently reset the entire UART subsystem for every recoverable error.

## 15. RTOS and Concurrency

Define thread-safety guarantees for all public APIs.

Consider:

- Multiple TX producers.
- RX producer and consumer.
- ISR-to-task communication.
- DMA-to-task communication.
- Multiple application clients.
- Bus or channel ownership.
- Callback execution context.

### Recommended design

- Use one RX producer and one or more controlled consumers.
- Use a TX queue to serialize messages.
- Use mutexes for task-level shared state.
- Use semaphores or task notifications for completion.
- Use ISR-safe APIs from interrupt context.
- Avoid holding locks while waiting for slow external devices.
- Define timeout and cancellation behavior.
- Prevent deadlocks from nested locks.

For bare-metal systems, use bounded critical sections and a clear ownership model.

## 16. Power Management and Initialization

Consider UART behavior during:

- MCU reset.
- Bootloader execution.
- Low-power entry.
- Low-power wake-up.
- Clock switching.
- Peripheral reset.
- External device reset.
- Power loss on the remote device.

### Initialization sequence

1. Enable the required peripheral and GPIO clocks.
2. Configure TX/RX pins and electrical settings.
3. Configure clock source and baud rate.
4. Configure frame format and flow control.
5. Configure FIFO and DMA if required.
6. Configure interrupt priorities.
7. Initialize buffers and state machines.
8. Clear stale status flags.
9. Enable receiver and transmitter.
10. Enable interrupts or start DMA reception.

Ensure initialization does not transmit unintended bytes or generate unexpected control-signal transitions.

## 17. Coding Standards

Follow the project's coding conventions and static-analysis rules.

General rules:

- Use fixed-width integer types.
- Use `size_t` for buffer lengths.
- Validate pointers and lengths.
- Avoid magic numbers.
- Define buffer ownership and lifetime.
- Avoid dynamic allocation in critical embedded paths unless justified.
- Keep ISRs short and deterministic.
- Avoid blocking operations in interrupt context.
- Use explicit state machines for asynchronous communication.
- Avoid unbounded loops.
- Document timeout semantics.
- Document overflow policies.
- Keep MCU-specific code isolated.

Do not use `volatile` as a substitute for synchronization.

Do not expose vendor-specific HAL types in a portable public API unless the project explicitly accepts that dependency.

## 18. Requirements Engineering

Convert system and hardware requirements into verifiable software requirements.

Example:

**Requirement: UART configuration**

The UART driver shall configure the selected peripheral according to the configured baud rate, data width, parity, stop bits, and flow-control mode.

**Requirement: RX buffering**

The UART communication service shall store received bytes in a bounded RX buffer and shall report buffer overflow according to the configured overflow policy.

**Requirement: asynchronous TX**

The UART driver shall not release or reuse a TX buffer before the corresponding asynchronous transfer has completed.

**Requirement: error handling**

The UART driver shall detect and report supported hardware communication errors.

**Requirement: framing**

The protocol parser shall process fragmented and concatenated input frames without assuming that individual receive events correspond to complete messages.

**Requirement: timeout**

The UART communication service shall detect a communication timeout according to the configured timeout definition.

Each requirement should have:

- Unique ID.
- Clear shall-statement.
- Defined preconditions.
- Measurable acceptance criteria.
- Verification method.
- Traceability to system or hardware requirements.

Avoid vague requirements such as "UART shall communicate reliably."

## 19. Verification and Testing

Testing must cover both byte-level communication and application-level protocol behavior.

### Unit tests

Test:

- Configuration validation.
- Baud-rate configuration calculations.
- Ring-buffer operations.
- Buffer overflow behavior.
- Packet framing.
- Parser state transitions.
- CRC validation.
- Timeout logic.
- Error mapping.
- TX queue behavior.

Use mocked hardware interfaces where appropriate.

### Integration tests

Test:

- UART initialization.
- TX and RX.
- Different baud rates.
- Different frame formats.
- Polling, interrupt, and DMA paths.
- Circular DMA wraparound.
- Receive-to-idle behavior.
- Multiple messages in one receive operation.
- Fragmented messages.
- Hardware flow control.
- RS-485 direction switching.
- Error recovery.

### Hardware tests

Use a logic analyzer or oscilloscope to verify:

- Baud rate.
- Bit period.
- Start and stop bits.
- Data bit order.
- Parity.
- TX/RX timing.
- RTS/CTS behavior.
- RS-485 driver-enable timing.
- Signal voltage levels.
- Signal integrity.

### Stress and fault tests

Test:

- Maximum supported baud rate.
- Continuous RX traffic.
- Maximum packet size.
- Back-to-back messages.
- Random packet fragmentation.
- RX buffer overflow.
- TX queue overflow.
- Disconnected remote device.
- Incorrect baud rate.
- Parity and framing errors.
- DMA errors.
- Clock changes.
- Reset during active transfer.
- Long-duration operation.

### Acceptance criteria

- No unintended data loss within specified operating conditions.
- No buffer overrun under the defined maximum traffic load.
- No deadlocks or unbounded waits.
- No use-after-free or premature DMA buffer reuse.
- Correct packet reconstruction.
- Correct error reporting and recovery.
- Timing requirements satisfied under worst-case conditions.

## 20. Agent Workflow

When asked to implement or modify UART functionality:

1. Inspect repository structure and coding conventions.
2. Identify MCU, UART instance, SDK, and hardware abstraction layer.
3. Inspect the reference manual and relevant device datasheets.
4. Identify baud rate, frame format, flow control, and electrical interface.
5. Identify traffic rate, maximum packet size, and latency requirements.
6. Determine whether the system is bare-metal or RTOS-based.
7. Select polling, interrupt, or DMA based on measured or calculated requirements.
8. Define RX/TX buffer ownership and concurrency behavior.
9. Define protocol framing and parser responsibilities.
10. Implement configuration validation.
11. Implement driver and communication-service logic.
12. Add timeout, overflow, error, and recovery handling.
13. Add unit and integration tests.
14. Run available builds, static analysis, and tests.
15. Review timing, memory usage, ISR execution, and buffer lifetime.
16. Document hardware assumptions and unresolved dependencies.

### Before modifying code

Inspect:

- Existing UART driver.
- Clock tree configuration.
- Board pin configuration.
- DMA configuration.
- Interrupt handlers.
- RTOS synchronization.
- Existing ring buffers and queues.
- External transceiver circuitry.
- Protocol documentation.

Do not replace an existing communication architecture without understanding its users.

### When hardware information is missing

Do not invent:

- Pin assignments.
- Baud-rate limits.
- DMA request mappings.
- FIFO sizes.
- Interrupt flag-clearing sequences.
- Transceiver timing.
- Electrical voltage levels.
- Protocol framing rules.

Use explicit placeholders and state what must be confirmed.

## 21. Expected Deliverables

Depending on the task, produce:

- UART architecture/design.
- Portable UART API.
- MCU-specific UART implementation.
- UART configuration.
- RX ring buffer.
- TX queue.
- Interrupt/DMA integration.
- Protocol framing and parser.
- Error handling and recovery.
- Unit and integration tests.
- Hardware verification procedure.
- Throughput and buffer-size analysis.
- Requirement-to-test traceability.

## 22. Senior Engineering Decision Principles

1. UART is a byte stream, not a packet protocol.
2. Separate electrical interface, UART driver, and application protocol.
3. DMA completion is not necessarily UART transmission completion.
4. RX buffering must be sized for worst-case processing delay.
5. IDLE detection is not a universal packet boundary.
6. Buffer ownership and lifetime must be explicit.
7. Error recovery must leave the driver in a defined state.
8. Flow control must account for bytes already in flight.
9. RS-485 direction switching must wait for the final stop bit.
10. `volatile` alone does not make shared data thread-safe.
11. Optimize using measured throughput, latency, and CPU utilization.
12. Verify hardware timing and electrical assumptions against documentation.

The goal is not merely to transmit and receive bytes. The goal is to build a deterministic, robust, test