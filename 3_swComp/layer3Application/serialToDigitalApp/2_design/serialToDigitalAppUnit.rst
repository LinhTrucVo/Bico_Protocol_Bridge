..  c:namespace:: SerialToDigitalApp

serialToDigitalAppUnit.c
###########################

Application layer component providing GPIO and PWM control. Called by the Central
Application Controller for RID 0x0201 (GPIO Write), 0x0202 (GPIO Read),
0x0301 (PWM Start), 0x0302 (PWM Stop). Delegates to GPIO and PWM drivers.

..  doxygenfile:: serialToDigitalAppUnit.c
    :project: SerialToDigitalApp