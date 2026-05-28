..  c:namespace:: DIGITALAPP

DIGITALAPPUnit.c
###########################

Application layer component providing GPIO and PWM control. Called by the Central
Application Controller for RID 0x0200 (GPIO Write), 0x0201 (GPIO Read),
0x0300 (PWM Start), 0x0301 (PWM Stop). Delegates to GPIO and PWM drivers.

..  doxygenfile:: DIGITALAPPUnit.c
    :project: DIGITALAPP