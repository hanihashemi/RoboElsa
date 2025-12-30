#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Most 0.91" SSD1306 modules are 128x32; change to 64 if needed.
static const uint8_t kScreenWidth = 128;
static const uint8_t kScreenHeight = 32;
static const uint8_t kOledAddress = 0x3C;

static const uint8_t kSdaPin = 21;
static const uint8_t kSclPin = 22;

Adafruit_SSD1306 display(kScreenWidth, kScreenHeight, &Wire, -1);

static void ScanI2C() {
  Serial.println("I2C scan...");
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found: 0x");
      if (addr < 16) {
        Serial.print('0');
      }
      Serial.println(addr, HEX);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Wire.begin(kSdaPin, kSclPin);
  ScanI2C();

  if (!display.begin(SSD1306_SWITCHCAPVCC, kOledAddress)) {
    Serial.println("SSD1306 init failed");
    while (true) {
      delay(100);
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hello ESP32");
  display.println("OLED 0.91");
  display.display();
}

void loop() {}
