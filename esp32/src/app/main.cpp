#include <Arduino.h>
#include "drivers/display.h"
#include "utils/logger.h"
#include "net/mqtt_client.h"
#include "net/transport.h"

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
