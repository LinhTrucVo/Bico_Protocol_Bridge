# Stub Directory

This directory contains stub implementations for testing DataConversionService.

## Purpose

Stubs are simplified implementations of dependencies that are used during testing.
They provide minimal functionality to support test execution without requiring
the full dependency implementation.

## Usage

1. Create stub files for external dependencies
2. Implement minimal required functionality
3. Link stub files in test CMakeLists.txt when needed

## Example

\\\c
// stub_hardware.c - Stub for hardware access
uint32_t HW_ReadRegister(uint32_t address) {
    return 0; // Stub returns fixed value
}
\\\

## Guidelines

- Keep stubs simple and focused
- Document any assumptions or limitations
- Use stubs when mocks or fakes are too complex
