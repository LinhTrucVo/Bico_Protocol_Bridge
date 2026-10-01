//file: main.cpp
#include "Arduino.h"
#define LED_PIN 8

extern "C"
{
#include "centralAppController.h"
#include "comService.h"
}

void setup(){
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("begin");

  // The central application controller initializes the services and, through them, the drivers.
  if (CentralAppControllerUnit_Init() != CENTRAL_APP_CONTROLLER_STATUS_OK) {
    Serial.println("central application controller init failed");
  }
}

void loop(){
  (void)ComServiceUnit_Run();
  (void)CentralAppControllerUnit_Run();
  delay(1);

  Serial.println("LED ON");
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  Serial.println("LED OFF");
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
