# ============================================================
# Sphinx configuration: ASPICE 4.0
# Scope: SWE.1 - SWE.6
# Target: Sphinx-Needs 9.x
# ============================================================

# ============================================================
# 1. NEED TYPES
# ============================================================

needs_types = [
    {
        "directive": "sw_req",
        "title": "Software Requirement",
        "description": "Defines what the software shall do to satisfy user and system requirements. Describes the expected software capabilities, features, and constraints from the software's perspective.",
        "prefix": "SWREQ_",
        "color": "#BFD8D2",
        "style": "node",
    },
    {
        "directive": "swc_req",
        "title": "Software Component Requirement",
        "description": "Defines the detailed functional and non-functional requirements allocated to individual software components identified in the software architecture. Specifies what each software component shall do to fulfill its allocated responsibilities.",
        "prefix": "SWCREQ_",
        "color": "#D6EAF8",
        "style": "node",
    },
    {
        "directive": "sw_arch",
        "title": "Software Architecture",
        "description": "Describes the high-level structure and organization of the software. Identifies software components, their responsibilities, relationships, interactions, and architectural interfaces.",
        "prefix": "SWARCH_",
        "color": "#D6EAF8",
        "style": "node",
    },
    {
        "directive": "sw_detail",
        "title": "Software Detailed Design",
        "description": "Refines the software architecture and realizes software component requirements into implementable design specifications. Defines detailed component behavior, algorithms, interfaces, data types, data structures, constraints, boundaries, limits, and valid values.",
        "prefix": "SWDD_",
        "color": "#E8DAEF",
        "style": "node",
    },
    {
        "directive": "swc",
        "title": "Software Component",
        "description": "Represents an architectural software component and its implementation. Implements the detailed design as buildable and executable software code, fulfilling the responsibilities and requirements allocated to the component.",
        "prefix": "SWC_",
        "color": "#E8DAEF",
        "style": "node",
    },
    {
        "directive": "sw-if",
        "title": "Software Interface",
        "description": "Defines a logical connection and interaction point between software components or between the software and external entities. Groups a set of related interface elements into a reusable interface contract, which may be represented by a file, class, or other software artifact.",
        "prefix": "SWIF_",
        "color": "#E8DAEF",
        "style": "node",
    },
    {
        "directive": "sw-ifelement",
        "title": "Software Interface Element",
        "description": "Defines an individual element of a software interface, such as a function, method, parameter, signal, data structure, or data type. Specifies the individual interaction or data exchange capability provided by the interface.",
        "prefix": "SWIFE_",
        "color": "#E8DAEF",
        "style": "node",
    },
    {
        "directive": "sw_unit",
        "title": "Software Unit",
        "description": "Represents the smallest independently verifiable software element resulting from detailed design and implementation. Typically corresponds to a function, method, class, or other implementation-level element.",
        "prefix": "SWUNIT_",
        "color": "#D5F5E3",
        "style": "node",
    },
    {
        "directive": "sw_unit_test",
        "title": "Software Unit Verification",
        "description": "Defines verification activities and test cases that verify individual software units against their detailed design specifications. Checks correctness of implementation, including behavior, boundary conditions, and relevant error handling.",
        "prefix": "SWUT_",
        "color": "#FCF3CF",
        "style": "node",
    },
    {
        "directive": "sw_integration_test",
        "title": "Software Integration Verification",
        "description": "Defines verification activities and test cases that verify the interaction and integration of software components against the software architecture. Checks interfaces, communication, data exchange, and interaction behavior between integrated components.",
        "prefix": "SWIT_",
        "color": "#FADBD8",
        "style": "node",
    },
    {
        "directive": "sw_qualification_test",
        "title": "Software Qualification Test",
        "description": "Defines validation activities and test cases that verify the integrated software against software requirements. Confirms that implemented software features behave as expected and satisfy the specified functional and non-functional requirements.",
        "prefix": "SWQT_",
        "color": "#F5CBA7",
        "style": "node",
    },
]


# ============================================================
# 2. CUSTOM FIELDS AND ALLOWED VALUES
# ============================================================
#
# Values supplied for these fields must match their enum.
# Matching is case-sensitive.
#
# These fields remain optional. If a field is omitted, its
# enum does not require the author to supply a value.
#
# Example:
#   :priority: high       -> valid
#   :priority: urgent     -> invalid
#   :priority: High       -> invalid

needs_fields = {
    "provides": {
        "description": "Interface header and function summary a component provides (swc).",
        "schema": {
            "type": "string",
        },
    },

    "requires": {
        "description": "Interface headers a component uses from the layer below (swc).",
        "schema": {
            "type": "string",
        },
    },

    "arguments": {
        "description": "Return type and parameters as '<name>: <C type>;' list (sw-ifelement).",
        "schema": {
            "type": "string",
        },
    },

    "priority": {
        "description": "Project-defined priority.",
        "schema": {
            "type": "string",
            "enum": [
                "critical",
                "high",
                "medium",
                "low",
            ],
        },
    },

    "verification_method": {
        "description": "Verification method planned or performed.",
        "schema": {
            "type": "string",
            "enum": [
                "inspection",
                "analysis",
                "demonstration",
                "test",
            ],
        },
    },

    "verification_result": {
        "description": "Outcome of a verification activity.",
        "schema": {
            "type": "string",
            "enum": [
                "not_run",
                "passed",
                "failed",
                "blocked",
                "not_applicable",
            ],
        },
    },
}


# IMPORTANT:
# Enable Sphinx-Needs schema validation explicitly.
# This validates field schemas, including enum restrictions.
needs_schema_validation_enabled = True


# ============================================================
# 3. TRACEABILITY LINKS
# ============================================================
#
# Relationship direction:
#
# SWARCH --realizes--> SWREQ
# SWCREQ --derives--> SWREQ
# SWDD   --realizes--> SWCREQ
# SWDD   --refines--> SWARCH
# SWC    --refines--> SWARCH
# SWUNIT --implements--> SWDD or SWIFE
#
# SWC (swc), SWIF (sw-if) and SWIFE (sw-ifelement) are the interface part of the
# detailed design (SWE.3): component, its public interface, one element per function.
#
# SWUT --verifies--> SWDD or SWIFE
# SWIT --verifies--> SWARCH
# SWQT --verifies--> SWREQ
#
# Reverse link fields are generated automatically:
# realizes_back, derives_back, refines_back, implements_back, verifies_back.
#
# target_types restricts the target of a link.
# It does not restrict the source type using that link.

needs_links = {
    "realizes": {
        "incoming": "realized by",
        "outgoing": "realizes",
        "target_types": [
            "sw_req",
            "swc_req",
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#1F77B4",
    },

    "derives": {
        "incoming": "derived by",
        "outgoing": "derives",
        "target_types": [
            "sw_req",
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#17A589",
    },

    "refines": {
        "incoming": "refined by",
        "outgoing": "refines",
        "target_types": [
            "sw_arch",
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#9467BD",
    },

    "implements": {
        "incoming": "implemented by",
        "outgoing": "implements",
        "target_types": [
            "sw_detail",
            "sw-ifelement",
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#2CA02C",
    },

    "verifies": {
        "incoming": "verified by",
        "outgoing": "verifies",
        "target_types": [
            "sw_detail",
            "sw-ifelement",
            "sw_arch",
            "sw_req",
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#D62728",
    },
}


# ============================================================
# 4. AUTOMATIC TRACEABILITY WARNINGS
# ============================================================
#
# These checks run automatically for every matching need.
# No per-need :constraints: option is required.
#
# Each expression describes an invalid condition.
# When the expression matches a need, Sphinx-Needs reports
# the warning using the corresponding check name.
#
# NOTE:
# These checks validate link existence, not engineering
# correctness or full ASPICE process compliance.

needs_warnings = {
    # --------------------------------------------------------
    # SWE.1 - Software Requirements Analysis
    # --------------------------------------------------------

    # Every software requirement must be realized by
    # at least one architecture element.
    "swe1_requirement_without_architecture": (
        'type == "sw_req" and not realizes_back'
    ),

    # Every software requirement must have a verification
    # link from at least one qualification-test item.
    "swe1_requirement_without_verification": (
        'type == "sw_req" and not verifies_back'
    ),

    # Every allocated system requirement must be decomposed into
    # at least one software-component requirement.
    "swe2_requirement_without_component_requirement": (
        'type == "sw_req" and not derives_back'
    ),

    # --------------------------------------------------------
    # SWE.2 - Software Architectural Design
    # --------------------------------------------------------

    # Every architecture element must realize a requirement.
    "swe2_architecture_without_requirement": (
        'type == "sw_arch" and not realizes'
    ),

    # Every component requirement must derive from a system requirement.
    "swe2_component_requirement_without_requirement": (
        'type == "swc_req" and not derives'
    ),

    # Every component requirement must be realized by detailed design.
    "swe2_component_requirement_without_design": (
        'type == "swc_req" and not realizes_back'
    ),

    # Every architecture element must be refined by
    # at least one detailed-design item.
    "swe2_architecture_without_detailed_design": (
        'type == "sw_arch" and not refines_back'
    ),

    # --------------------------------------------------------
    # SWE.3 - Detailed Design and Unit Construction
    # --------------------------------------------------------

    # Every detailed-design item must refine an architecture
    # element.
    "swe3_design_without_architecture": (
        'type == "sw_detail" and not refines'
    ),

    # Every detailed-design item must realize a component requirement.
    "swe3_design_without_component_requirement": (
        'type == "sw_detail" and not realizes'
    ),

    # Every detailed-design item must be implemented by
    # at least one software unit.
    "swe3_design_without_software_unit": (
        'type == "sw_detail" and not implements_back'
    ),

    # Every software unit must link to its detailed design.
    "swe3_unit_without_detailed_design": (
        'type == "sw_unit" and not implements'
    ),

    # --------------------------------------------------------
    # SWE.4 - Software Unit Verification
    # --------------------------------------------------------

    # Every detailed-design item must have at least one unit-test
    # verification link.
    "swe4_design_without_unit_verification": (
        'type == "sw_detail" and not verifies_back'
    ),

    # Every unit-test item must link to a verification target.
    "swe4_test_without_unit_target": (
        'type == "sw_unit_test" and not verifies'
    ),

    # --------------------------------------------------------
    # SWE.5 - Software Integration Verification
    # --------------------------------------------------------

    # Every integration-test item must have a target.
    "swe5_integration_test_without_target": (
        'type == "sw_integration_test" and not verifies'
    ),

    # --------------------------------------------------------
    # SWE.6 - Software Qualification Test
    # --------------------------------------------------------

    # Every qualification-test item must link to a requirement.
    "swe6_qualification_test_without_requirement": (
        'type == "sw_qualification_test" and not verifies'
    ),
}


# ============================================================
# 5. NEED ID AND JSON EXPORT SETTINGS
# ============================================================

# Require explicit IDs for needs.
needs_id_required = True

# Export needs data to JSON during the build.
needs_build_json = True


# ============================================================
# 6. SPHINX-NEEDS 5.x COMPATIBILITY
# ============================================================
#
# The docGen image pins sphinx_needs 5.1.0. It ignores needs_fields and
# needs_links, so the old option names are derived from the definitions above.

from importlib.metadata import version as _package_version

if int(_package_version("sphinx-needs").split(".")[0]) < 6:
    needs_extra_options = list(needs_fields)
    needs_extra_links = [
        {
            "option": name,
            "incoming": link["incoming"],
            "outgoing": link["outgoing"],
            "style_start": link["style_start"],
            "style_end": link["style_end"],
            "style": link["style"],
        }
        for name, link in needs_links.items()
    ]