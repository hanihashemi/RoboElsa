#include <Arduino.h>
#include <PubSubClient.h>
#include <string.h>

#include "config.h"
#include "logger.h"
#include "mqtt_client.h"
#include "transport.h"

static PubSubClient mqtt;
static char mqttClientId[32];

static void OnMqttMessage(char *topic, byte *payload, unsigned int length) {
  char message[64];
  size_t copyLen = length < sizeof(message) - 1 ? length : sizeof(message) - 1;
  memcpy(message, payload, copyLen);
  message[copyLen] = '\0';
  Logf("MQTT %s: %s", topic, message);
}

static void BuildMqttClientId() {
  uint64_t chipId = ESP.getEfuseMac();
  snprintf(mqttClientId, sizeof(mqttClientId), "car-%04X%08X",
           static_cast<uint16_t>(chipId >> 32),
           static_cast<uint32_t>(chipId));
}

static bool EnsureMqttConnected() {
  if (mqtt.connected()) {
    return true;
  }
  LogLine("MQTT connecting...");
  if (mqtt.connect(mqttClientId)) {
    mqtt.subscribe(kMqttCmdTopic);
    mqtt.publish(kMqttStatusTopic, "online");
    LogLine("MQTT connected");
    return true;
  }
  Logf("MQTT connect failed, rc=%d", mqtt.state());
  return false;
}

void MqttBegin() {
  BuildMqttClientId();
  mqtt.setClient(TransportClient());
  mqtt.setServer(kMqttHost, kMqttPort);
  mqtt.setCallback(OnMqttMessage);
  EnsureMqttConnected();
}

void MqttLoop() {
  static uint32_t lastMqttAttemptMs = 0;

  if (!mqtt.connected()) {
    uint32_t now = millis();
    if (now - lastMqttAttemptMs > 5000) {
      lastMqttAttemptMs = now;
      EnsureMqttConnected();
    }
    return;
  }

  mqtt.loop();
}
