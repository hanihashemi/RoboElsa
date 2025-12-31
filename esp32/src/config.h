#pragma once

#include <Arduino.h>

// Most 0.91" SSD1306 modules are 128x32; change to 64 if needed.
static const uint8_t kScreenWidth = 128;
static const uint8_t kScreenHeight = 32;
static const uint8_t kOledAddress = 0x3C;

static const uint8_t kSdaPin = 21;
static const uint8_t kSclPin = 22;

static const char *kMqttHost = "192.168.1.108";
static const uint16_t kMqttPort = 1883;
static const char *kMqttCmdTopic = "car/cmd";
static const char *kMqttStatusTopic = "car/status";

#if defined(TRANSPORT_WIFI)
static const char *kWifiSsid = "Hani";
static const char *kWifiPass = "96089637";
#endif

#if defined(TRANSPORT_GSM)
static const char *kGsmApn = "YOUR_APN";
static const char *kGsmUser = "";
static const char *kGsmPass = "";
static const uint32_t kGsmBaud = 115200;

#ifndef GSM_RX
#define GSM_RX 26
#endif
#ifndef GSM_TX
#define GSM_TX 27
#endif
#ifndef GSM_PWRKEY
#define GSM_PWRKEY -1
#endif
#endif
