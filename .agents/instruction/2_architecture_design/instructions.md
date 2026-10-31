---
name: swe2-architecture-design
description: Use when software requirements in 1_requirement are new or changed and the software architecture in 2_architecture must be created or updated (ASPICE SWE.2).
---

# SWE.2 Software Architectural Design

Read `AGENTS.md` first.

## Scope

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- The architecture ends at the HAL boundary. A layer1 driver calls only its own port API `<Drv>Port_*` (declared in `3_1_swComp/layer1Driver/<drv>/3_inc/<drv>Porting.h`). How a hardware workspace implements the port is not part of this architecture.

## Inputs

- `1_requirement/<Feature>/index.rst` (`sw_req` needs)
- Existing `2_architecture/`

## Outputs

- `2_architecture/fucntionView/<layer>/<comp>/` with `index.rst`, `staticView.puml`, `informationFlow.puml`, `dynamicBehaviour.puml`
- `2_architecture/deploymentView/` only when the port boundary or build integration changes
- A new component is added to the toctree in `2_architecture/fucntionView/index.rst`

## Steps

1. List the `sw_req` needs that are new or changed.
2. Allocate each one to components following ISO/IEC/IEEE 42010. Respect the layers: `layer3Application` -> `layer2Service` -> `layer1Driver` -> `<Drv>Port_*`. A layer calls only the layer directly below.
3. For each affected component, update `index.rst` with: Description, Static view, Information flow, Dynamic behaviour, Timing behaviour, Resource consumption, and the interfaces it provides and uses.
4. For a layer1 driver, name the HAL operations it needs (e.g. GPIO: init/configure, read, write, toggle) as port interface, using standard C types only.
5. List the affected components in the answer so SWE.3 can update them.

## Traceability

```rst
.. sw_arch:: GPIO driver
   :id: SWARCH_GPIODRIVER
   :realizes: SWREQ_DIGITAL_001, SWREQ_DIGITAL_002
```

- One `sw_arch` per component, `:id:` is `SWARCH_<COMP>`.
- Every `sw_arch` has `:realizes:` to at least one `sw_req`.

## Done criteria

- Every new or changed `sw_req` is realized by at least one `sw_arch`.
- `5_buildEnviroment/docGen/docGen.sh` builds without errors and without the warnings `swe1_requirement_without_architecture` and `swe2_architecture_without_requirement`. `swe2_architecture_without_detailed_design` is expected until SWE.3 is done.