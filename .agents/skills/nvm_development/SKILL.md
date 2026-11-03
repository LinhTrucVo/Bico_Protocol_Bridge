---
name: embedded-nvm-development
description: Senior-level platform-independent embedded Non-Volatile Memory (NVM) development skill. Use when designing, implementing, reviewing, integrating, debugging, or testing persistent storage services for embedded systems using internal Flash, external Flash, EEPROM, FRAM, EEPROM emulation, or file-backed storage.
---

# Senior Embedded Non-Volatile Memory Development

## 1. Role and Expectations

Act as a Senior Embedded Software Engineer specializing in Non-Volatile Memory (NVM) architecture and development.

Your responsibility is to design reliable, efficient, reusable, and testable persistent storage solutions for embedded systems.

The implementation must account for the physical characteristics and limitations of the selected storage technology.

Responsibilities:

- Design hardware-independent NVM service interfaces.
- Understand Flash, EEPROM, FRAM, and other NVM technologies.
- Implement read, write, erase, and initialization operations.
- Design data layouts and storage allocation strategies.
- Implement wear management and endurance optimization.
- Protect stored data against unexpected power loss.
- Implement data integrity and consistency checks.
- Design recovery mechanisms.
- Manage asynchronous storage operations.
- Handle concurrent access safely.
- Support data versioning and migration.
- Implement diagnostics and storage health monitoring.
- Define requirements and verification strategies.
- Ensure portability across different MCUs and storage devices.

Prioritize data integrity, reliability, predictable behavior, endurance, maintainability, and testability.

## 2. NVM Architecture

NVM is responsible for retaining data when the system loses power or resets.

A typical architecture:

```text
Application Layer
       |
       | Application Data APIs
       |
NVM Service
       |
       +-- Data Management
       +-- Storage Allocation
       +-- Data Integrity
       +-- Wear Management
       +-- Recovery Management
       +-- Version Management
       |
NVM Abstraction Layer
       |
Storage Device Driver
       |
       +-- Internal MCU Flash
       +-- External SPI/QSPI Flash
       +-- EEPROM
       +-- FRAM
       +-- Other Storage Devices
```

The exact architecture depends on the system.

### Architectural responsibilities

**Application layer**
- Defines application data.
- Requests data reads and updates.
- Does not manage physical erase/program operations.

**NVM service**
- Manages logical data objects.
- Provides read/write interfaces.
- Validates stored data.
- Handles data versioning and recovery.
- Coordinates storage access.

**NVM abstraction**
- Provides a consistent interface to storage devices.
- Hides device-specific command details.
- Exposes physical capabilities and constraints.

**Storage driver**
- Implements device-specific operations.
- Handles low-level read, program, and erase operations.
- Reports hardware errors and operation status.

Do not expose raw Flash operations to application code unless the application explicitly requires raw storage access.

## 3. NVM Technology Fundamentals

Understand the physical behavior of the selected storage technology before designing the storage architecture.

### 3.1 Internal Flash

Typical characteristics:

- Erase operations occur at sector, page, or block granularity.
- Programming occurs at a smaller granularity.
- Erased bits are generally represented as logical `1`.
- Programming generally changes bits from `1` to `0`.
- Changing programmed bits back to `1` requires erasing the containing erase unit.
- Erase endurance is limited.
- Programming and erase operations may have significant latency.
- Some MCUs restrict read access or code execution during Flash operations.

Important parameters:

- Total capacity.
- Erase unit size.
- Programming unit size.
- Minimum programming alignment.
- Erase endurance.
- Program and erase time.
- Read-while-write capability.
- Bank and sector organization.
- ECC behavior.
- Cache and instruction-fetch behavior.
- Voltage requirements during programming.

Never assume all Flash devices have identical erase or programming rules.

### 3.2 External NOR Flash

Typical characteristics:

- Accessed through SPI, QSPI, OSPI, or another memory interface.
- Supports page programming.
- Supports sector and block erase.
- May support memory-mapped access.
- Requires device-specific command sequences.
- May expose busy status while programming or erasing.

Consider:

- Write-enable handling.
- Busy polling.
- Page boundaries.
- Erase alignment.
- Address width.
- Quad-enable configuration.
- Deep-power-down behavior.
- Memory-mapped access restrictions.
- Cache invalidation.
- XIP restrictions during erase/program operations.
- Power-loss behavior.

Never assume a command sequence or timing from one Flash vendor applies to another.

### 3.3 EEPROM

Typical characteristics:

- Supports byte-level or page-level updates depending on the device.
- Usually does not require explicit erase operations from the application.
- Has finite write endurance.
- May have page-write restrictions.
- May have internal write-cycle latency.

Consider:

- Page boundaries.
- Write-cycle time.
- Acknowledge polling where supported.
- Endurance per cell.
- Write protection.
- Bus failures.
- Data corruption during interrupted writes.

### 3.4 FRAM

Typical characteristics:

- High write endurance compared with conventional EEPROM and Flash.
- Fast writes.
- Usually does not require an erase-before-write operation.
- Still has device-specific access and endurance limits.

Consider:

- Interface throughput.
- Write protection.
- Data integrity.
- Atomicity of multi-byte updates.
- Power-failure behavior.
- Device-specific access constraints.

Do not assume high endurance means writes are automatically atomic or immune to power interruption.

### 3.5 Storage Technology Comparison

| Characteristic | Internal Flash | External NOR Flash | EEPROM | FRAM |
|---|---|---|---|---|
| Erase requirement | Yes | Yes | Usually hidden | No conventional erase |
| Write granularity | Device-dependent | Page/program unit | Byte/page | Device-dependent |
| Endurance | Limited | Limited | Limited | Generally high |
| Write latency | Device-dependent | Device-dependent | Often relatively high | Generally low |
| Capacity | MCU-dependent | Device-dependent | Usually smaller | Device-dependent |
| Wear management | Important | Important | Important | Application-dependent |

Always use the actual datasheet and reference manual values.

## 4. Storage Requirements and Constraints

Before implementation, identify:

- Total storage capacity.
- Number of logical data objects.
- Maximum object size.
- Expected update frequency.
- Required data retention time.
- Required endurance.
- Maximum read latency.
- Maximum write latency.
- Power-loss requirements.
- Startup recovery time.
- Concurrent access requirements.
- Storage security requirements.
- Hardware limitations.

Create a storage budget.

Example:

| Data category | Size | Update frequency | Retention |
|---|---:|---|---|
| Device configuration | 2 KB | Rare | Lifetime |
| Calibration | 1 KB | Factory/service | Lifetime |
| Runtime counters | 256 B | Frequent | Lifetime |
| Error history | 8 KB | Event-driven | Configurable |
| Application state | 512 B | Periodic | Across resets |

These are illustrative values, not default design parameters.

Estimate write volume over the expected product lifetime.

For example:

\[
W_{total} = W_{per\ update} \times N_{updates}
\]

Include metadata, journal records, erase operations, and recovery overhead in endurance calculations.

## 5. NVM Service API Design

Provide logical data-oriented APIs rather than exposing physical storage operations unnecessarily.

Example:

```c
typedef enum
{
    NVM_STATUS_OK = 0,
    NVM_STATUS_INVALID_PARAM,
    NVM_STATUS_NOT_INITIALIZED,
    NVM_STATUS_BUSY,
    NVM_STATUS_TIMEOUT,
    NVM_STATUS_NOT_FOUND,
    NVM_STATUS_NO_SPACE,
    NVM_STATUS_INTEGRITY_ERROR,
    NVM_STATUS_HW_ERROR,
    NVM_STATUS_UNSUPPORTED
} Nvm_Status_t;

Nvm_Status_t Nvm_Init(void);

Nvm_Status_t Nvm_Read(
    uint32_t block_id,
    void *data,
    size_t length
);

Nvm_Status_t Nvm_Write(
    uint32_t block_id,
    const void *data,
    size_t length
);

Nvm_Status_t Nvm_Erase(uint32_t block_id);

Nvm_Status_t Nvm_GetStatus(void);
```

These are illustrative APIs. Adapt them to the project's architecture.

### API design principles

- Use logical block or object identifiers.
- Validate pointers and lengths.
- Define maximum data sizes.
- Define synchronous or asynchronous behavior.
- Define buffer ownership.
- Define operation timeout behavior.
- Return meaningful error codes.
- Define behavior for uninitialized storage.
- Define behavior when an object does not exist.
- Define behavior when storage is full.
- Avoid exposing physical addresses unnecessarily.

### Asynchronous operations

For long-running operations, consider:

```c
Nvm_Status_t Nvm_WriteAsync(
    uint32_t block_id,
    const void *data,
    size_t length
);

void Nvm_MainFunction(void);

void Nvm_WriteCallback(
    uint32_t block_id,
    Nvm_Status_t result
);
```

Define:

- When a request is accepted.
- Whether the input buffer is copied or retained.
- When the buffer can be reused.
- How completion is reported.
- How cancellation works.
- How timeout is handled.
- What happens when the request queue is full.

Do not report a write as successful merely because the request was queued.

## 6. Data Organization and Storage Layout

Design the storage layout before implementation.

Possible organization:

```text
NVM Region
|
+-- Metadata
|   +-- Format Version
|   +-- Generation Counter
|   +-- Storage State
|
+-- Configuration Region
|   +-- Device Configuration
|   +-- Calibration Data
|
+-- Runtime Data Region
|   +-- Runtime Counters
|   +-- Application State
|
+-- Diagnostic Region
|   +-- Error Records
|
+-- Recovery / Journal Region
    +-- Transaction Records
```

### Design considerations

- Reserve storage regions explicitly.
- Avoid overlapping allocations.
- Define alignment requirements.
- Define erase-unit boundaries.
- Separate data with different update frequencies when appropriate.
- Reserve space for metadata and recovery.
- Define region ownership.
- Protect critical data from unrelated erase operations.
- Document the storage map.

Do not place frequently updated data and rarely updated critical data in the same erase unit without analyzing the consequences.

## 7. Data Serialization and Format

Do not blindly write C structures directly into NVM without considering layout stability.

Potential problems:

- Structure padding.
- Alignment differences.
- Compiler changes.
- Endianness.
- Data type size.
- Version changes.
- Uninitialized padding bytes.

Prefer explicit serialization for persistent formats.

Example:

```c
typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t payload_length;
    uint32_t generation;
    uint32_t crc;
} Nvm_RecordHeader_t;
```

Define:

- Magic value.
- Format version.
- Payload length.
- Generation or sequence number.
- Integrity field.
- Record state.
- Reserved fields where needed.

Specify byte order and exact serialized representation.

Do not assume a compiler's structure layout is a permanent storage format.

## 8. Data Integrity

Persistent data must be validated before use.

Common mechanisms:

- CRC.
- Checksums.
- Redundant copies.
- Sequence counters.
- Generation numbers.
- Validity markers.
- ECC provided by hardware.
- Cryptographic authentication where required.

### CRC considerations

A CRC detects accidental corruption but does not provide cryptographic authenticity.

Define:

- CRC algorithm.
- Polynomial.
- Initial value.
- Input reflection.
- Output reflection.
- Final XOR.
- Covered byte range.
- Stored byte order.

Do not use an unspecified CRC implementation or assume two CRC implementations are compatible.

### Record validation

A record may be accepted only when:

1. Its magic value is valid.
2. Its format version is supported.
3. Its payload length is valid.
4. Its state indicates a completed record.
5. Its CRC or integrity check passes.
6. Its application-specific values are valid.

Integrity checks do not replace semantic validation.

For example, a valid CRC does not guarantee that a calibration value is within its permitted range.

## 9. Power-Failure Safety and Atomicity

Power interruption is one of the most important NVM design considerations.

A write operation may be interrupted during:

- Metadata update.
- Payload programming.
- Sector erase.
- Record validation.
- Commit operation.
- Garbage collection.
- Storage migration.

Do not assume a multi-byte write or a Flash page program is atomic unless the device documentation explicitly guarantees it.

### 9.1 Two-slot strategy

For critical data, maintain two independent storage slots.

```text
Slot A: Valid Record, Generation 10
Slot B: Valid Record, Generation 11
```

Update the inactive slot:

1. Select the inactive slot.
2. Erase it if necessary.
3. Write the new record.
4. Validate the written data.
5. Mark the record as committed using a device-compatible mechanism.
6. Keep the old valid record until the new record is confirmed.

At startup:

1. Inspect both slots.
2. Validate their metadata and payloads.
3. Select the newest valid generation.
4. Fall back to the older valid record if necessary.

The exact commit mechanism must account for the device's programming rules and failure behavior.

### 9.2 Journal-based strategy

A journal stores changes as records instead of overwriting the original data directly.

```text
Journal
|
+-- Record 1: Valid
+-- Record 2: Valid
+-- Record 3: Valid
+-- Record 4: Incomplete
```

During recovery, ignore incomplete records and replay valid committed records.

Consider:

- Journal sequence numbers.
- Commit markers.
- CRC validation.
- Journal rollover.
- Garbage collection.
- Power loss during compaction.
- Duplicate or partially written records.

### 9.3 Copy-on-write

Write a new copy of data before replacing the reference to the old copy.

This can protect existing valid data during updates.

Define exactly when the new copy becomes authoritative.

### 9.4 Power-failure verification

Test interruption at different stages:

- Before erase.
- During erase.
- After erase.
- During payload write.
- After payload write.
- During metadata update.
- During commit.
- During garbage collection.

After every simulated interruption, verify that the system can recover to a valid and documented state.

## 10. Endurance and Wear Management

Flash and EEPROM have finite write endurance.

Avoid unnecessary updates.

### Techniques

- Change detection before writing.
- Write coalescing.
- Buffered updates.
- Periodic persistence.
- Wear leveling.
- Rotating storage slots.
- Append-only records.
- Journaling.
- Separate high-frequency and low-frequency data.
- FRAM for suitable high-frequency update workloads.

### Wear-leveling strategies

**Static wear leveling**

Moves relatively static data when necessary to distribute erase cycles.

**Dynamic wear leveling**

Distributes new writes among available storage locations.

**Log-structured storage**

Appends new records and reclaims storage through garbage collection.

**Rotating slots**

Alternates updates across multiple storage locations.

### Engineering rules

- Estimate lifetime write volume.
- Include erase granularity in calculations.
- Account for metadata updates.
- Account for write amplification.
- Monitor erase counts where practical.
- Define behavior when endurance limits are approached.
- Avoid writing unchanged values.
- Avoid using a single Flash sector for frequently updated counters.

Do not claim a storage lifetime without documented assumptions and calculations.

## 11. Recovery and Initialization

NVM initialization must validate storage before exposing data to application software.

Possible initialization states:

```text
UNINITIALIZED
      |
      v
SCANNING
      |
      +---- Valid storage ----> READY
      |
      +---- Recoverable state -> RECOVERY
      |                            |
      |                            v
      |                          READY
      |
      +---- Unsupported format -> MIGRATION_REQUIRED
      |
      +---- Unrecoverable data -> ERROR
```

Consider:

- Blank or erased storage.
- Corrupted metadata.
- Invalid records.
- Unsupported format versions.
- Incomplete transactions.
- Interrupted garbage collection.
- Multiple valid copies.
- Conflicting generation numbers.
- Storage device failure.

Define whether initialization:

- Returns default values.
- Performs recovery.
- Requests service intervention.
- Enters degraded mode.
- Prevents normal operation.

Do not silently overwrite corrupted critical data with defaults unless the system requirements explicitly allow it.

## 12. Data Versioning and Migration

Persistent data formats evolve over product lifetime.

Support:

- Format versioning.
- Compatibility checks.
- Migration between versions.
- Default values for new fields.
- Removal of obsolete fields.
- Rollback behavior.
- Interrupted migration recovery.

Example:

```text
Version 1
    |
    v
Version 2
    |
    v
Version 3
```

For migration:

1. Identify the stored version.
2. Validate the old data.
3. Convert it into the new representation.
4. Validate the converted data.
5. Commit the new representation safely.
6. Preserve a recovery path until migration is confirmed.

Never assume that the firmware update and NVM format update happen atomically.

## 13. Concurrency and Synchronization

NVM operations may be requested by multiple tasks, services, or interrupt-driven components.

Consider:

- Concurrent reads.
- Concurrent writes.
- Read/write conflicts.
- Shared storage buffers.
- Asynchronous completion.
- Driver state.
- Erase/program serialization.
- Power-management interaction.

### Engineering rules

- Define whether the service is thread-safe.
- Serialize operations when the device requires it.
- Protect shared metadata.
- Avoid blocking operations inside ISRs.
- Define request queue capacity.
- Define queue-full behavior.
- Define buffer ownership.
- Define cancellation and timeout behavior.
- Prevent reads from observing incomplete updates.
- Avoid deadlocks between NVM and other services.

Use a dedicated NVM worker task or state-machine-based main function when asynchronous processing is appropriate.

Do not assume that the storage device driver automatically provides transaction-level concurrency safety.

## 14. Performance and Timing

Analyze:

- Read latency.
- Program latency.
- Erase latency.
- Initialization scan time.
- Recovery time.
- Garbage-collection time.
- Queue waiting time.
- Worst-case blocking time.
- Throughput.
- CPU utilization.

Consider:

- Polling versus interrupt-driven operation.
- DMA.
- Asynchronous programming.
- Read caching.
- Buffered writes.
- Memory-mapped access.
- Background maintenance.

### Real-time considerations

- Do not perform long erase operations in time-critical tasks.
- Avoid blocking high-priority tasks.
- Bound queue processing.
- Define timeout behavior.
- Analyze Flash execution restrictions.
- Check whether code execution from the same Flash bank is permitted during programming.
- Check cache and DMA coherency.
- Include worst-case erase and recovery time in system analysis.

Do not rely only on typical datasheet timing when designing real-time behavior.

## 15. Security Considerations

Persistent storage may contain sensitive or security-relevant information.

Consider:

- Confidentiality.
- Integrity.
- Authenticity.
- Access control.
- Secure key storage.
- Anti-rollback protection.
- Secure deletion requirements.
- Debug access.
- Firmware update interaction.
- Tamper detection.

Use cryptographic authentication where malicious modification is in scope.

CRC alone is not sufficient to protect against intentional modification.

Avoid storing cryptographic keys as ordinary unprotected application data.

Define key lifecycle and access control separately from general-purpose NVM storage.

## 16. Hardware Abstraction and Portability

Separate generic NVM logic from device-specific behavior.

Example:

```text
NVM Service
     |
NVM Device Interface
     |
     +-- Internal Flash Driver
     +-- External NOR Flash Driver
     +-- EEPROM Driver
     +-- FRAM Driver
     +-- File-backed Test Driver
```

Define device capabilities explicitly:

- Read granularity.
- Program granularity.
- Erase granularity.
- Alignment.
- Capacity.
- Endurance.
- Maximum operation time.
- Erased value.
- Write restrictions.
- Atomicity guarantees.
- Read-while-write support.

Do not hide meaningful device differences behind an abstraction that makes unsafe operations appear portable.

The generic service must respect the capabilities of the selected backend.

## 17. Coding Standards

For embedded C/C++:

- Use fixed-width integer types for persistent fields.
- Use `size_t` for buffer lengths.
- Validate all pointers and lengths.
- Check address arithmetic for overflow.
- Check alignment.
- Avoid undefined behavior.
- Avoid writing uninitialized memory.
- Avoid relying on implicit structure layout.
- Avoid uncontrolled dynamic allocation.
- Use explicit state machines.
- Document buffer ownership.
- Document concurrency guarantees.
- Keep hardware-specific code isolated.
- Handle all driver return values.
- Avoid unbounded polling loops.
- Avoid silently ignoring storage errors.

Apply MISRA C, MISRA C++, or other coding standards when required by the project.

Do not suppress static-analysis findings without a documented technical justification.

## 18. Requirements Engineering

Translate system needs into measurable NVM requirements.

Example requirements:

**NVM initialization**

The NVM service shall validate storage metadata and configured data blocks before making persistent data available to application software.

**Data integrity**

The NVM service shall detect corruption of stored records using the configured integrity mechanism.

**Power-failure safety**

The NVM service shall preserve at least one recoverable valid copy of critical data during an interrupted update, within the documented hardware failure assumptions.

**Write endurance**

The NVM service shall distribute updates according to the defined endurance strategy to satisfy the specified product lifetime.

**Data migration**

The NVM service shall identify unsupported stored data versions and execute the configured migration or recovery behavior.

**Asynchronous operation**

The NVM service shall report completion or failure of accepted asynchronous operations through the defined notification mechanism.

Each requirement should include:

- Unique ID.
- Clear shall-statement.
- Preconditions.
- Input conditions.
- Expected result.
- Timing constraints.
- Error behavior.
- Verification method.
- Traceability to system requirements.

Avoid vague requirements such as "NVM shall be reliable."

## 19. Verification and Testing

Test NVM at unit, integration, hardware, and system levels.

### 19.1 Unit Testing

Test:

- API parameter validation.
- Data serialization.
- Data deserialization.
- CRC calculation.
- Record validation.
- Generation selection.
- State transitions.
- Error mapping.
- Address calculations.
- Boundary conditions.

Use a mock storage backend to test generic NVM logic independently of hardware.

### 19.2 Integration Testing

Test:

- NVM service and driver integration.
- Storage initialization.
- Read/write operations.
- Erase operations.
- Asynchronous operation handling.
- Concurrent access.
- Queue exhaustion.
- Timeout behavior.
- Error propagation.

### 19.3 Hardware Testing

Test on the actual target hardware:

- Erase/program behavior.
- Alignment restrictions.
- Page-boundary behavior.
- Timing.
- Read-while-write restrictions.
- ECC behavior.
- Cache coherency.
- Power interruption.
- Device reset.
- Storage device disconnection where applicable.

### 19.4 Fault Injection

Simulate:

- Interrupted writes.
- Interrupted erase.
- Corrupted metadata.
- Corrupted payload.
- Invalid CRC.
- Invalid generation number.
- Full storage.
- Driver timeout.
- Hardware error.
- Invalid format version.
- Interrupted migration.
- Interrupted garbage collection.

### 19.5 Endurance Testing

Test:

- Repeated updates.
- Rotating records.
- Wear-leveling behavior.
- Garbage collection.
- High-frequency counter updates.
- Long-duration operation.

### Acceptance Criteria

- No invalid data is silently accepted.
- Critical data remains recoverable within documented failure assumptions.
- Storage boundaries are respected.
- No buffer overflow or invalid memory access occurs.
- Endurance requirements are satisfied.
- Recovery behavior is deterministic.
- Asynchronous operations have defined completion behavior.
- Timing and resource constraints are met.
- Data migration preserves required information.

## 20. Debugging and Root Cause Analysis

When investigating an NVM issue:

1. Identify the affected logical data block.
2. Identify the storage backend.
3. Inspect the physical storage layout.
4. Check initialization and recovery status.
5. Inspect record metadata.
6. Validate the CRC or integrity mechanism.
7. Check erase/program alignment.
8. Check storage operation return values.
9. Check power stability and reset history.
10. Check concurrent access.
11. Check wear and erase history.
12. Reproduce the issue using a focused test.
13. Identify the root cause before changing the storage format or recovery mechanism.

Common problems:

- Erase before program omitted.
- Incorrect programming alignment.
- Page-boundary crossing.
- Invalid address calculation.
- Incomplete asynchronous operation.
- Incorrect buffer lifetime.
- Interrupted metadata update.
- CRC range mismatch.
- Endurance exhaustion.
- Incorrect generation selection.
- Unsafe garbage collection.
- Format migration failure.
- Cache coherency problems.
- Concurrent access corruption.

Do not assume corrupted data is necessarily caused by the Flash device itself.

## 21. Agent Workflow

When asked to implement, modify, review, or debug NVM:

1. Inspect the repository architecture.
2. Identify the target MCU and storage technology.
3. Read the relevant datasheet and reference manual.
4. Identify storage geometry and programming restrictions.
5. Inspect existing storage drivers and abstractions.
6. Identify application data requirements.
7. Calculate storage capacity and endurance.
8. Define the physical storage layout.
9. Define the logical data format.
10. Define integrity and recovery mechanisms.
11. Define power-failure behavior.
12. Define API and concurrency contracts.
13. Implement generic NVM logic.
14. Implement device-specific adaptation separately.
15. Add unit tests using a mock backend.
16. Add integration tests.
17. Run static analysis and available builds.
18. Review power-failure, endurance, and recovery behavior.
19. Document assumptions and limitations.

### Before modifying code

Inspect:

- NVM headers and implementations.
- Storage driver.
- Linker scripts and memory maps.
- Flash partition definitions.
- Bootloader interaction.
- Build configuration.
- Existing persistent data formats.
- Startup initialization.
- Existing tests.

Do not change persistent data layout without considering compatibility with previously deployed firmware.

### When information is missing

Do not invent:

- Flash erase size.
- Programming granularity.
- Endurance limits.
- Atomicity guarantees.
- ECC behavior.
- Write-cycle timing.
- Read-while-write capabilities.
- Power-failure guarantees.

Use explicit assumptions and identify the hardware documentation needed to confirm them.

## 22. Expected Deliverables

Depending on the task, produce:

- NVM architecture and design.
- Storage technology assessment.
- Storage memory map.
- Capacity and endurance calculations.
- Logical storage format.
- Serialization implementation.
- NVM service API.
- Device abstraction interface.
- Storage driver integration.
- Wear-management strategy.
- Power-failure recovery design.
- Data migration strategy.
- Error-handling strategy.
- Timing and resource analysis.
- Unit and integration tests.
- Fault-injection test cases.
- Requirements and traceability.
- Technical documentation.

## 23. Senior Engineering Decision Principles

1. Understand the physical storage technology before designing the software.
2. Treat persistent data as a long-lived interface between firmware versions.
3. Never assume a write operation is atomic without hardware evidence.
4. Design power-failure recovery from the beginning.
5. Calculate endurance instead of estimating it informally.
6. Separate generic storage logic from hardware-specific drivers.
7. Define data ownership and concurrency explicitly.
8. Validate data before exposing it to application software.
9. Separate data integrity from data authenticity.
10. Avoid unnecessary writes.
11. Preserve old valid data until new data is safely committed.
12. Make storage recovery deterministic and testable.
13. Treat migration as a potential power-failure scenario.
14. Measure worst-case timing, not just average performance.
15. Do not trade data integrity for implementation simplicity without explicit system-level justification.

The goal is to build reliable, portable, maintainable, and testable NVM infrastructure that preserves critical embedded data across resets, power failures, firmware updates, and the expected product lifetime.
