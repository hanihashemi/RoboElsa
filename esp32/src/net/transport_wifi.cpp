#if defined(TRANSPORT_WIFI)
#include <Arduino.h>
#include <WiFi.h>

#include "config/config.h"
#include "utils/logger.h"
#include "net/transport.h"

static WiFiClient wifiClient;

bool TransportBegin() {
  Logf("WiFi connecting to %s", kWifiSsid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(kWifiSsid, kWifiPass);

  uint32_t startMs = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startMs > 15000) {
      LogLine("WiFi connect timeout");
      return false;
    }
    delay(250);
  }

  Logf("WiFi connected, IP: %s", WiFi.localIP().toString().c_str());
  return true;
}

Client &TransportClient() { return wifiClient; }

const char *TransportName() { return "WiFi"; }
#endif
