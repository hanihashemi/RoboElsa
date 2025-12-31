#include <Arduino.h>
#include <stdarg.h>
#include <string.h>

#include "display.h"
#include "logger.h"

static const size_t kLogLineCount = 4;
static const size_t kMaxLineLen = 22;

static bool logReady = false;
static char logLines[kLogLineCount][kMaxLineLen];

static void CopyLine(char *dest, const char *src) {
  if (!src) {
    dest[0] = '\0';
    return;
  }
  snprintf(dest, kMaxLineLen, "%s", src);
}

static void PushLine(const char *message) {
  for (size_t i = 0; i + 1 < kLogLineCount; ++i) {
    memmove(logLines[i], logLines[i + 1], kMaxLineLen);
  }
  CopyLine(logLines[kLogLineCount - 1], message);

  if (logReady) {
    DisplayShowLines(logLines[0], logLines[1], logLines[2], logLines[3]);
  }
}

void LogBegin() {
  for (size_t i = 0; i < kLogLineCount; ++i) {
    logLines[i][0] = '\0';
  }
  logReady = true;
  DisplayShowLines(logLines[0], logLines[1], logLines[2], logLines[3]);
}

void LogLine(const char *message) {
  Serial.println(message);
  PushLine(message);
}

void Logf(const char *fmt, ...) {
  char buffer[96];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  Serial.println(buffer);
  PushLine(buffer);
}
