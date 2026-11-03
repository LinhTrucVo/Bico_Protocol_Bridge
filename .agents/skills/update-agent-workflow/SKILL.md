---
name: update_agent_workflow
description: "Use when the user asks to change, update, add or remove anything in the Bico Protocol Bridge agent workflow: AGENTS.md, .agents/instruction/*, .agents/index.rst or its puml diagrams, gates, roles, traceability (Sphinx-Needs types and links), or the agents in .github/agents and .claude/agents. Propagates the change to every related file so the workflow stays consistent."
---

# Update the agent workflow

The agents are built from the common instructions in `.agents/instruction/` and the common rules in `AGENTS.md`.
When one of them changes, every file that restates it must change in the same task.

Do not read or write `7_x_*` hardware workspaces, `.claude/agent-memory`, or `_build`.

## Terminology

The files in `.agents/instruction/` are called **instruction** (never "skill"). They are given to an agent by explicit path, not picked by the model.

## Where each fact lives

| Changed | Also update |
|---|---|
| `.agents/instruction/<step>/instructions.md` (inputs, outputs, need type, link, ID, done criteria) | Instruction table in `AGENTS.md`; Traceability table in `.agents/index.rst`; `.agents/sweTraceability.puml`; `5_buildEnviroment/docGen/aspice_config.py` (`needs_links`, `needs_warnings`, comment block); other instructions that reference it; agent files that cite it |
| SWE.3 interface design needs (`swc`, `sw-if`, `sw-ifelement`) | `.agents/instruction/aspice_swe3_detailed_design_unit_construction/instructions.md`; `.agents/instruction/aspice_swe4_unit_verificationion/instructions.md`; each component's `2_design/<comp>Comp.rst`; `AGENTS.md`; `.agents/index.rst`; ARCHITECT, DESIGNER and CODER agent files |
| SWE.2 component requirement need (`swc_req`), derivation and design realization links | SWE.2/SWE.3/SWE.4 instructions; `aspice_config.py`; `AGENTS.md`; `.agents/index.rst`; `.agents/sweTraceability.puml`; ARCHITECT, DESIGNER and LEADER agent files |
| `AGENTS.md` (scope rules, repository map, conventions, team table, verification) | `.agents/index.rst` (terms, Agent team, Rules); `Constraints` and `Tasks` of the agent files; `README.md` and `5_buildEnviroment/README.md` if they repeat it |
| Gates, roles, who writes or reviews what | `.agents/index.rst` (Agent team, Gates, Delegated task); `agentTeam.puml`, `workflowGates.puml`, `taskSequence.puml`; `AGENTS.md` team table; `.github/agents/leader.agent.md` and the agent files of the roles involved |
| Agent definition in `.github/agents/<name>.agent.md` (description, tools, constraints, checklist, report format) | `.claude/agents/<name>.md`: `description` identical, body still points to the `.github` file; any other agent directory (for example `.cursor`, `.gemini`) |
| Skill in `.agents/skills/<name>/SKILL.md` (name, description) | `.claude/skills/<name>/SKILL.md` and `.github/skills/<name>/SKILL.md` wrappers: same `name` and `description`, body points to the `.agents/skills` file |
| Need types, IDs, links | `aspice_config.py` (keep the section that derives `needs_extra_options` and `needs_extra_links` for the pinned sphinx_needs 5.1.0); instruction of the step; `.agents/index.rst`; `sweTraceability.puml`; `AGENTS.md`; templates in `0_ticket/ticket_template.rst` |
| Build or verification commands, coverage limit | `AGENTS.md` Verification; `.agents/index.rst` (G4, G5, Builds); `integrator.agent.md`; `.github/workflows/ci.yml`; `5_buildEnviroment/README.md` |

## Steps

1. State the requested change in one sentence and list the rows of the table above that apply.
2. Update the source of truth first (the instruction or `AGENTS.md`), then each dependent file from the table.
3. Search for every old term, ID or link name across `AGENTS.md`, `.agents`, `.github/agents`, `.claude/agents`, `agents_plan.md` and `5_buildEnviroment/docGen`, and fix remaining hits.
4. Keep the `.claude/agents`, `.claude/skills` and `.github/skills` wrappers thin: they reference the `.github/agents` or `.agents/skills` file and do not restate its content.
5. Ask user if anything conflicted or not clear.
6. Report the changed files and anything that needs a user decision.

## Do not

- Leave a table, diagram or agent file with the old behaviour.
- Add content to a wrapper in `.claude/agents`, `.claude/skills` or `.github/skills` that is not in the file it points to.
- Change instructions or agents beyond what the user asked for.
