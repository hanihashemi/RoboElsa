#if defined(TRANSPORT_GSM)
#define TINY_GSM_MODEM_A7670
#include <Arduino.h>
#include <TinyGsmClient.h>

#include "config/config.h"
#include "utils/logger.h"
#include "net/transport.h"

static HardwareSerial SerialAT(2);
static TinyGsm modem(SerialAT);
static TinyGsmClient netClient(modem);

static void PulseGsmPwrKey() {
#if GSM_PWRKEY >= 0
  pinMode(GSM_PWRKEY, OUTPUT);
  digitalWrite(GSM_PWRKEY, LOW);
  delay(100);
  digitalWrite(GSM_PWRKEY, HIGH);
  delay(1000);
  digitalWrite(GSM_PWRKEY, LOW);
  delay(1000);
#endif
}

bool TransportBegin() {
  LogLine("GSM starting...");
  SerialAT.begin(kGsmBaud, SERIAL_8N1, GSM_RX, GSM_TX);
  PulseGsmPwrKey();
  delay(300);

  if (!modem.restart()) {
    LogLine("GSM restart failed");
    return false;
  }
  if (!modem.waitForNetwork(60000L)) {
    LogLine("GSM network not found");
    return false;
  }
  if (!modem.gprsConnect(kGsmApn, kGsmUser, kGsmPass)) {
    LogLine("GSM APN connect failed");
    return false;
  }

  LogLine("GSM connected");
  return true;
}

Client &TransportClient() { return netClient; }

const char *TransportName() { return "GSM"; }
#endif
