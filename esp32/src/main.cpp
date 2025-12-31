#include <Arduino.h>
#include "display.h"
#include "logger.h"
#include "mqtt_client.h"
#include "transport.h"

void setup() {
  Serial.begin(115200);
  delay(200);
  DisplayBegin();
  LogBegin();
  LogLine("Booting...");

  if (!TransportBegin()) {
    Logf("Transport failed: %s", TransportName());
    return;
  }

  MqttBegin();
}

void loop() {
  MqttLoop();
}
