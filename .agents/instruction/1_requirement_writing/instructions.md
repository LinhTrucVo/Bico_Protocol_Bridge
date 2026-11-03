---
name: swe1-requirement-analysis
description: Use when the user asks to turn a ticket in 0_ticket into new or changed software requirements in 1_requirement (ASPICE SWE.1).
---

# SWE.1 Software Requirements Analysis

Read `AGENTS.md` first. Start only when the user requests it.

## Scope

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- Requirements describe behaviour seen at the serial interface and at the peripheral pins. They never name a microcontroller, SDK or vendor API.

## Inputs

- The ticket named by the user in `0_ticket/<yymmdd>_<hhmmss>.rst` (format: `0_ticket/ticket_template.rst`: Title, Description, Expected Result)
- Existing `1_requirement/<Feature>/index.rst`

## Outputs

- `1_requirement/<Feature>/index.rst`, one folder per feature (e.g. `SerialToDigital`)
- Diagrams in the same folder: `userBenefit.puml`, `useCase.puml`
- A new feature folder is added to the toctree in `1_requirement/index.rst`

## Steps

1. Read the ticket. If the Expected Result is missing or contradicts existing requirements, ask the user before writing.
2. Find the affected feature folder, or create one with the sections: feature description, User benefits, Use case, Requirements, Verification criteria.
3. Write each requirement as one `sw_req` need, following ISO/IEC/IEEE 29148:
   - One "shall" statement per requirement: singular, unambiguous, verifiable, free of implementation.
   - Give values with units and ranges (baud rate, pin range, timing).
4. Give every requirement a verification criterion that a qualification test (SWE.6) can check.

## Traceability

```rst
.. sw_req:: Digital output write
   :id: SWREQ_DIGITAL_001
   :priority: high
   :verification_method: test

   The system shall set a digital output pin to the level given in the write command.
```

- `:id:` is `SWREQ_<FEATURE>_<NNN>`. Never reuse or renumber an existing ID.
- `:priority:` is one of `critical`, `high`, `medium`, `low` (case-sensitive).
- `:verification_method:` is one of `inspection`, `analysis`, `demonstration`, `test` (case-sensitive).

## Done criteria

- Every point of the ticket Expected Result maps to at least one `sw_req`.
- `5_buildEnviroment/docGen/docGen.sh` builds without errors. The warnings `swe1_requirement_without_architecture` and `swe1_requirement_without_verification` are expected until SWE.2 and SWE.6 are done.