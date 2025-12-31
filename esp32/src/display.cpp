#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "display.h"

static Adafruit_SSD1306 display(kScreenWidth, kScreenHeight, &Wire, -1);
static bool displayReady = false;

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

void DisplayBegin() {
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
  display.println("Hello");
  display.println("Hani und Radin Studio");
  display.display();
  displayReady = true;
}

void DisplayShowLines(const char *line1, const char *line2, const char *line3,
                      const char *line4) {
  if (!displayReady) {
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(line1 ? line1 : "");
  display.println(line2 ? line2 : "");
  display.println(line3 ? line3 : "");
  display.println(line4 ? line4 : "");
  display.display();
}
