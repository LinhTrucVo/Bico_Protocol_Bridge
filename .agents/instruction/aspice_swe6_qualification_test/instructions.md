---
name: swe6-qualification-test
description: Use when the user asks for software qualification tests in 4_2_qualificationTest that verify the software requirements in 1_requirement (ASPICE SWE.6).
---

# SWE.6 Software Qualification Test

Read `AGENTS.md` first.

## Status: blocked

The HIL (hardware-in-the-loop) environment is not prepared yet, so qualification tests cannot be executed.

- Do not write qualification test specifications, test code or `sw_qualification_test` needs.
- Tell the user that SWE.6 is blocked until the HIL environment exists, and stop.
- The warning `swe1_requirement_without_verification` in the documentation build is expected while this step is blocked.

## Scope (for when the block is lifted)

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- Input: `1_requirement/<Feature>/index.rst` (`sw_req` and verification criteria).
- Output: `4_2_qualificationTest/`, need type `sw_qualification_test` with `:verifies:` to `sw_req`, ID `SWQT_<FEATURE>_<NNN>`.
