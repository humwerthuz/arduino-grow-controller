#include "DeviceController.h"

void DeviceController::setLogger(Logger *l) {
  logger = l;
}

const char* DeviceController::getDeviceName() {
  return this->deviceName;
}

void DeviceController::setDeviceName(const char *name) {
  this->deviceName = name;
}

void DeviceController::setApiSink(APIClient *sink) {
  this->apiSink = sink;
}

void DeviceController::sinkData(const char *eventType, const char *eventValue, const char *eventLocation) const {
  if(this->apiSink == nullptr) return;

  char buff[256];
  snprintf(buff, sizeof(buff), R"({"eventType":"%s", "eventValue":"%s", "eventLocation":"%s"})", eventType, eventValue, eventLocation);
  this->apiSink->send(buff);
}

void DeviceController::tick() {

}
