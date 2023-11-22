#include "FanController.h"
#include "constants.h"

FanController::FanController(int fcPin, const char *name) {
    setDeviceName(name);
    ds18instance = nullptr;
    ds18address = nullptr;
    fanControlPin = fcPin;
    stopTemp = 0;
    startTemp = 0;
    lastState = LOW;
    pinMode(fanControlPin, OUTPUT);
    digitalWrite(fanControlPin, lastState);
}

void FanController::setTemperatureRange(float start, float stop) {
  this->startTemp = start;
  this->stopTemp = stop;
}

void FanController::tick(){
  this->ds18instance->requestTemperaturesByAddress(this->ds18address);
  float actualTemp = this->ds18instance->getTempC(this->ds18address);
  if (this->logger != nullptr) {
    std::string logBuff = "Device " + std::string(this->getDeviceName()) + " got temperature " + std::to_string(actualTemp);
    logger->logInfo(logBuff.c_str());
  }

  this->sinkData(TagTemperatureEvent, std::to_string(actualTemp).c_str(), this->getDeviceName());

  if ( actualTemp >= this->startTemp && this->lastState != HIGH) {
    this->lastState = HIGH;
    digitalWrite(this->fanControlPin, this->lastState);
    this->sinkData(TagFanEvent, TagOn, this->getDeviceName());
  } else if ( actualTemp <= this->stopTemp && this->lastState != LOW) {
    this->lastState = LOW;
    digitalWrite(this->fanControlPin, this->lastState);
   this->sinkData(TagFanEvent, TagOff, this->getDeviceName());
  }
}

void FanController::setTemperatureProbe(DallasTemperature *ds18, uint8_t *address) {
  this->ds18instance = ds18;
  this->ds18address = address;
}
