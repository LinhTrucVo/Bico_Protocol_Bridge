.. Descrive about the Nvm Service component requirements
Overall requirements
********************

The NVM Service shall provide key-based storage for configuration and calibration data.
The component shall protect data integrity using CRC.

Input validation
****************

The component shall validate key identifiers, data pointers, and length parameters.
The component shall reject blobs exceeding the maximum supported size.

Requirements for component
**************************

Req-nvmService-001: The component shall save a data blob under a specified key.
   Verification: Save stores the blob and returns OK for valid inputs.

Req-nvmService-002: The component shall load a stored blob for a specified key.
   Verification: Load returns the stored data and length for existing keys.

Req-nvmService-003: The component shall erase a stored blob by key.
   Verification: Erase removes the key and Exists returns false afterward.

Req-nvmService-004: The component shall support erasing all stored blobs.
   Verification: EraseAll clears all keys.

Req-nvmService-005: The component shall verify data integrity using CRC.
   Verification: Load returns CRC_ERROR when stored CRC does not match data.

Req-nvmService-006: The component shall return NOT_FOUND for missing keys.
   Verification: Load returns NOT_FOUND when key does not exist.

Req-nvmService-007: The component shall return INVALID_PARAM for null pointers or oversized inputs.
   Verification: Save and Load return INVALID_PARAM for invalid inputs.
