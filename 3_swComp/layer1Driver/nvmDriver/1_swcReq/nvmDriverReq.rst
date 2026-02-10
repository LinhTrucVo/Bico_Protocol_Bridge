.. Descrive about the NVM Driver component requirements
Overall requirements
********************

The NVM Driver shall provide a hardware abstraction for non-volatile memory operations.
The component shall support read, write, and erase operations with integrity checking.

Input validation
****************

The component shall validate addresses, buffer pointers, and length parameters.
The component shall reject operations outside the configured memory range.

Requirements for component
**************************

Req-nvmDriver-001: The component shall initialize the NVM peripheral with configuration data.
   Verification: Init returns OK for valid configuration values.

Req-nvmDriver-002: The component shall read data from a specified address.
   Verification: Read returns the expected data for valid addresses.

Req-nvmDriver-003: The component shall write data to a specified address.
   Verification: Write stores data and Verify confirms integrity.

Req-nvmDriver-004: The component shall erase pages, sectors, and full chip.
   Verification: ErasePage, EraseSector, and EraseChip complete successfully.

Req-nvmDriver-005: The component shall calculate CRC for a memory region.
   Verification: CalculateCrc returns expected CRC for reference data.

Req-nvmDriver-006: The component shall support write protection enable/disable.
   Verification: EnableWriteProtection blocks writes and DisableWriteProtection allows writes.
