---
name: swe3-detailed-design-unit-construction
description: Use when the architecture in 2_architecture is new or changed and a software component in 3_1_swComp must be designed or coded - interface design (swc, sw-if, sw-ifelement), detailed design, HAL (port) API declaration and C source (ASPICE SWE.3).
---

# SWE.3 Software Detailed Design and Unit Construction

Read `AGENTS.md` first. Unit tests are written with the SWE.4 instruction (`.agents/instruction/aspice_swe4_unit_verificationion/instructions.md`).

## Scope

- Do not read or write `7_1_esp32_workspace` or any `7_x_*` hardware workspace.
- Code is hardware independent: no vendor header (`esp_*`, `driver/*`, `Arduino.h`, `freertos/*`, `stm32*`, ...), no register access, no `#ifdef` per target.
- A layer1 driver reaches the hardware only through the HAL (port) API it declares itself. Write the declaration, never the implementation; hardware workspaces implement it.
- `3_2_thirdPartiesSwComp` is read-only.

## Inputs

- `1_requirement/<Feature>/index.rst` (`sw_req`)
- `2_architecture/fucntionView/<layer>/<comp>/` (`sw_arch`)
- `3_1_swComp/<layer>/<comp>/1_swcReq/<comp>Req.rst` (`swc_req` needs written by SWE.2; read-only here)
- Existing `3_1_swComp/<layer>/<comp>/`

## Outputs

In `3_1_swComp/<layer>/<comp>/` (`<layer>` is `layer1Driver`, `layer2Service` or `layer3Application`):

| Path | Content |
|---|---|
| `2_design/<comp>Comp.rst` | Component design document with the static structure, interface design (`swc`, `sw-if`, `sw-ifelement`) and component-level detailed design (`sw_detail`) |
| `2_design/<comp>Unit.rst`, `<comp>Cfg.rst` | Unit and configuration detailed design (`sw_detail`) |
| `2_design/<comp>StaticStructure.puml`, `<comp>StateMachine.puml`, `<comp>SequenceDiagram.puml` | Design diagrams |
| `3_inc/<comp>.h` | Public API for the layer above |
| `3_inc/<drv>Porting.h` | HAL (port) API, layer1 drivers only |
| `4_config/<comp>Cfg.h` | Default configuration (may be overridden by a hardware workspace) |
| `5_src/<comp>Unit.c`, `5_src/<comp>Unit.h` | Implementation (`sw_unit`) |
| `CMakeLists.txt` | Library target |

A new component also creates `1_swcReq/` (if SWE.2 has not), `6_test/gtest/{fake,mock,stub}/`, `7_tools/index.rst`, `8_misc/index.rst`, is added to `3_1_swComp/bicoProtocolBridgeSwComp.cmake` and to the toctree in `3_1_swComp/index.rst`.

## HAL (port) API rules (layer1 drivers)

1. Declared in `3_inc/<drv>Porting.h`, functions named `<Drv>Port_<Action>` (e.g. `GpioPort_Init`, `GpioPort_ConfigurePin`, `GpioPort_Read`, `GpioPort_Write`, `GpioPort_Toggle`).
2. Only standard C types (`stdint.h`, `stdbool.h`) and enums/structs declared in the same header.
3. Minimal and generic: the smallest set of operations every target can provide. Parameter checks, state, buffering and callback dispatch stay in `<drv>Unit.c`.
4. Every function returns a status (`bool` or a `BPB_` enum) unless it cannot fail.
5. Callbacks that may run in interrupt context are documented as such in a one-line comment.
6. A change to `<drv>Porting.h` is an interface change for every hardware workspace: state it in the report.

## Coding rules

- Every macro and enum value starts with `BPB_`. Include guards: `BPB_<FILE>_H`.
- A layer includes only `3_inc` headers of the layer directly below.
- Every macors must be in `4_config`.
- Public functions validate pointers and ranges and return an error status instead of crashing.
- Code follows MISRA C:2012. A deviation needs a one-line comment `MISRA deviation: <rule> - <reason>`.

## Interface design (`swc`, `sw-if`, `sw-ifelement`)

The DESIGNER defines the public interface and detailed design from the architecture (`sw_arch`) and the component requirements (`swc_req`), and chooses the best form. Each design item realizes the component requirement(s) it implements. The result is written directly below the static-structure UML in `2_design/<comp>Comp.rst` and is the source for `3_inc/<comp>.h`.

- `swc`: the component. `:provides:` public header and what it offers, `:requires:` headers of the layer below (layer1: its own `<drv>Porting.h`), `:refines:` its `sw_arch`.
- `sw-if`: the public interface (the header that declares the functions), one per component.
- `sw-ifelement`: one per public function. `:arguments:` is `return: <type>; <name>: <type>; ...` with the exact types of the header. The body has the fields `Arguments`, `Return values`, `Restrictions`.

Design rules for every `sw-ifelement`:

1. **Parameter count:** as few as the function needs, at most 4. Related values go into one `const <Comp>_<Name>_t *` structure instead of more parameters. A function does one thing.
2. **Data type:** the smallest fixed-width type (`stdint.h`) that holds the value range; `bool` only for a true binary choice; an `enum` for a fixed set; no `int`/`long`. Lengths and counts `uint16_t`, timeouts in milliseconds `uint32_t`.
3. **Direction:** inputs by value or `const` pointer, outputs by pointer. Say for every pointer whether `NULL` is allowed.
4. **Value range and valid values:** every argument states its type, minimum and maximum (or the allowed enum values), unit, and what the function returns when it is outside. Limits are `BPB_` macros in `4_config`, not literals.
5. **Return values:** every status code and the condition that causes it. Every function returns a status unless it cannot fail.
6. **Restrictions:** required state (for example `Init` called first), blocking or timing behaviour, reentrancy, interrupt context.
7. The signature in `:arguments:` is identical to `3_inc/<comp>.h`; a change in one changes the other.

## Steps

The step has two phases. The design phase ends with gate G3: `3_inc` and `4_config` are frozen and the code phase starts.

**Design phase (DESIGNER)**

1. Find the changed `sw_arch` items: `git diff -U1000 <base> -- 2_architecture` (`<base>` given by LEADER), and the components that refine them.
2. Read `1_swcReq/<comp>Req.rst`. Do not change it; if a component requirement is wrong or incomplete, return a finding for ARCHITECT.
3. Write the interface design directly below the static-structure UML in `2_design/<comp>Comp.rst` (`swc`, `sw-if`, `sw-ifelement`, see Interface design) and update `2_design` (`sw_detail`, `sw_unit` IDs): units, data types, state machine, sequence for every public function. Each `sw_detail` refines its `sw_arch` and realizes the `swc_req` it implements; together, the design items cover every component requirement.
4. Update `3_inc` and `4_config` from the interface design. They must be final: tests and code are written against them in parallel.
5. A new component needs registration (`bicoProtocolBridgeSwComp.cmake`, toctree): edit only if LEADER granted the file, otherwise request it.

**Code phase (CODER)**

6. Implement `5_src` from `2_design`, `3_inc`, `4_config` and the `sw-ifelement` items of `2_design/<comp>Comp.rst`. Do not change them; return an interface change request instead.

## Traceability

```rst
..  swc:: gpioDriver
    :id: SWC_GPIODRIVER
    :refines: SWARCH_GPIODRIVER
    :provides: gpioDriver.h - pin configuration and digital read/write.
    :requires: gpioDriverPorting.h - HAL (port) API.

..  sw-if:: gpioDriverUnit.h
    :id: SWIF_GPIODRIVER

    Public interface of gpioDriverUnit.

    ..  sw-ifelement:: GpioDriverUnit_WritePin()
        :id: SWIFE_GPIODRIVER_WRITEPIN
        :arguments: return: GpioDriver_Status_t; pin: GpioDriver_Pin_t; state: GpioDriver_State_t;

        Writes a logical state to a GPIO output pin.

        **Arguments:**

        - **pin**: ``0`` to ``BPB_GPIO_PIN_COUNT - 1``.
        - **state**: ``BPB_GPIO_STATE_LOW`` or ``BPB_GPIO_STATE_HIGH``.

        **Return values:** ``BPB_GPIO_STATUS_OK``; ``BPB_GPIO_STATUS_INVALID_PIN`` for a pin out of range.

        **Restrictions:** The pin must be configured as output.

.. swc_req:: GPIO driver configures a pin
    :id: SWCREQ_GPIODRIVER_001
    :derives: SWREQ_DIGITAL_001

    The GPIO Driver shall configure a pin using a supported mode and pull setting.

.. sw_detail:: GPIO driver pin configuration
   :id: SWDD_GPIODRIVER_CONFIGUREPIN
   :refines: SWARCH_GPIODRIVER
    :realizes: SWCREQ_GPIODRIVER_001

.. sw_unit:: gpioDriverUnit
   :id: SWUNIT_GPIODRIVER
   :implements: SWDD_GPIODRIVER_CONFIGUREPIN, SWIFE_GPIODRIVER_WRITEPIN
```

- `swc` ID `SWC_<COMP>`, `sw-if` ID `SWIF_<COMP>`, `sw-ifelement` ID `SWIFE_<COMP>_<FUNCTION>` (function name without `Unit_` prefix and `()`, upper case). Every one has an explicit `:id:`.
- `swc_req` IDs are `SWCREQ_<COMP>_<NNN>` and each has `:derives:` to one or more `sw_req` needs.
- `sw_detail` IDs: `SWDD_<COMP>_<ITEM>`, each with `:refines:` to a `sw_arch` and `:realizes:` to one or more `swc_req` needs.
- `sw_unit` IDs: `SWUNIT_<COMP>`, one per `5_src/<comp>Unit.c`, with `:implements:` to its `sw_detail` and `sw-ifelement` items.
- `sw_unit` links to design only; it does not link directly to `swc_req` or `sw_req`.

## Done criteria

- Every changed `sw_arch` is refined by at least one `sw_detail` or `swc`; every `swc_req` is realized by at least one `sw_detail`; every `sw_detail` is implemented by a `sw_unit`.
- Every public function in `3_inc/<comp>.h` has a `sw-ifelement` with type, range and valid values of every argument, return values and restrictions; the signatures are identical.
- No vendor header in `3_1_swComp`: `grep -rE "esp_|driver/|Arduino.h|freertos/|stm32" 3_1_swComp --include=*.[ch]` returns nothing.
- `5_buildEnviroment/docGen/docGen.sh` builds without new warnings.
- `5_buildEnviroment/unitTestBuild/unitTestBuild.sh` compiles.
