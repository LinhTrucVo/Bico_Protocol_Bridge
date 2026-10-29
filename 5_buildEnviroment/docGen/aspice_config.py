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
        "prefix": "SWREQ_",
        "color": "#BFD8D2",
        "style": "node",
    },
    {
        "directive": "sw_arch",
        "title": "Software Architecture",
        "prefix": "SWARCH_",
        "color": "#D6EAF8",
        "style": "node",
    },
    {
        "directive": "sw_detail",
        "title": "Software Detailed Design",
        "prefix": "SWDD_",
        "color": "#E8DAEF",
        "style": "node",
    },
    {
        "directive": "sw_unit",
        "title": "Software Unit",
        "prefix": "SWUNIT_",
        "color": "#D5F5E3",
        "style": "node",
    },
    {
        "directive": "sw_unit_test",
        "title": "Software Unit Verification",
        "prefix": "SWUT_",
        "color": "#FCF3CF",
        "style": "node",
    },
    {
        "directive": "sw_integration_test",
        "title": "Software Integration Verification",
        "prefix": "SWIT_",
        "color": "#FADBD8",
        "style": "node",
    },
    {
        "directive": "sw_qualification_test",
        "title": "Software Qualification Test",
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
# SWDD   --refines--> SWARCH
# SWUNIT --implements--> SWDD
#
# SWUT --verifies--> SWUNIT
# SWIT --verifies--> SWARCH or SWUNIT
# SWQT --verifies--> SWREQ
#
# Reverse link fields are generated automatically:
# realizes_back, refines_back, implements_back, verifies_back.
#
# target_types restricts the target of a link.
# It does not restrict the source type using that link.

needs_links = {
    "realizes": {
        "incoming": "realized by",
        "outgoing": "realizes",
        "target_types": [
            "sw_req",
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#1F77B4",
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
        ],
        "style_start": "-",
        "style_end": "->",
        "style": "#2CA02C",
    },

    "verifies": {
        "incoming": "verified by",
        "outgoing": "verifies",
        "target_types": [
            "sw_unit",
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

    # --------------------------------------------------------
    # SWE.2 - Software Architectural Design
    # --------------------------------------------------------

    # Every architecture element must realize a requirement.
    "swe2_architecture_without_requirement": (
        'type == "sw_arch" and not realizes'
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

    # Every software unit must have at least one unit-test
    # verification link.
    "swe4_unit_without_unit_verification": (
        'type == "sw_unit" and not verifies_back'
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