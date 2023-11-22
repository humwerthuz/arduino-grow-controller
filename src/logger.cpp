#include "logger.h"

Logger::Logger(HardwareSerial *ser, DS3231 *clock) {
  this->_serial = ser;
  this->_clock = clock;
}

void Logger::logLine(const char *line, const char *level){
  char s[128];
  DateTime now = RTClib::now(this->_clock->_Wire);
  snprintf(s, sizeof(s), R"({"timestamp":"%d", "payload":"%s", "level":"%s"})", now.unixtime(), line, level);
  this->_serial->println(s);
}

void Logger::logInfo(const char *line) {
  this->logLine(line, "info");
}

void Logger::logError(const char *line) {
  this->logLine(line, "error");
}

void Logger::logDebug(const char *line) {
  this->logLine(line, "debug");
}

void Logger::logWarn(const char *line) {
  this->logLine(line, "warn");
}