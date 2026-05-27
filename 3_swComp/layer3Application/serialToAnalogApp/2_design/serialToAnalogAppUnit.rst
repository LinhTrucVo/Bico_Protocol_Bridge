..  c:namespace:: SerialToAnalogApp

serialToAnalogAppUnit.c
###########################

Application layer component providing ADC channel reading. Called by the Central
Application Controller for RID 0x0100 (ADC Read). Delegates to the ADC driver
for hardware access.

..  doxygenfile:: serialToAnalogAppUnit.c
    :project: SerialToAnalogApp