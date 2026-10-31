Get the information from 2_architecture and 2_design in 3_sw_component_preparation
Integrate all required component (refer bicoProtocolBridgeSwComp.cmake) into a complete system, then implement the integration testing (using Gtest) based on the defined criteria.

Main criteria validated by integration testing
1	Interface compatibility	Components communicate using the correct interfaces, APIs, and protocols.
2	Data exchange	Data is transferred correctly between components without corruption, loss, or unexpected modification.
3	Functional behavior	Integrated components produce the expected results for specified use cases.
4	Interaction sequence	Components execute operations in the correct order and follow the expected state transitions.
5	Error handling	Errors, invalid inputs, timeouts, and communication failures are handled correctly.

For HAL API, use the same approach as in unit tests, creating fakes that store and check parameters in files, and manipulate return values according to the test cases.

Refer to AGENTS.md for more project overall goal

The implemented integration tests shall be in 4_1_integrationTest