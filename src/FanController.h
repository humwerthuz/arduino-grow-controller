#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H
#include "DeviceController.h"
#include <DallasTemperature.h>
#include <OneWire.h>
#include "logger.h"
#include "defines.h"

class FanController : public DeviceController {
  private:
    int fanControlPin;
    float startTemp;
    float stopTemp;
    DallasTemperature *ds18instance;
    const uint8_t *ds18address{};
    uint8_t lastState;
  public:
    FanController(int,const char*);
    void setTemperatureProbe(DallasTemperature *, const uint8_t*);
    void setTemperatureRange(float, float);
    void tick() override;
};

#endif