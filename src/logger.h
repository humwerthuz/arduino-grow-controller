#ifndef LOGGER_H
#define LOGGER_H
#include <Arduino.h>
#include <DS3231.h>
class Logger {
  private:
    HardwareSerial *_serial;
    DS3231 *_clock;
    void logLine(const char*, const char*);
  public:
    Logger(HardwareSerial*, DS3231*);
    void logInfo(const char*);
    void logError(const char*);
    void logDebug(const char*);
    void logWarn(const char*);
};
#endif