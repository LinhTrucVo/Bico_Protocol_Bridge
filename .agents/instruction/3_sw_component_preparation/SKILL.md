Get the information from 1_requirement and 2_architecture_design
Implement the software component by following the architecture and requirements
Output is not only the code but also the requirement in sw level (interface, constraint,...), design, unittests

Especially in units test, which API define from other component must be a fake, and the behavior of the fake should be controlled to simulate different scenarios, for HAL API, create the fake which take the passing parameter then stored in file, checking by read and compare the content in the file similar to what passing to HAL API, return value is also be in the file, the value of return is manipulate acccording to the testcase, then the return value shall be compare after fake HAL returned.

the components in 3_2_thirdPartiesSwComp is not considered for unittest.

Refer to AGENTS.md for more project overall goal
The implemented software component shall be in 3_sw_component