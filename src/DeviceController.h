#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H
#include "logger.h"
#include "ApiClient.h"

class DeviceController {
  private:
    const char *deviceName{};
  public:
    Logger *logger{};
    APIClient *apiSink{};
    virtual void tick();
    const char *getDeviceName();
    void setDeviceName(const char*);
    void setLogger(Logger*);
    void setApiSink(APIClient*);
    void sinkData(const char*, const char*, const char*) const;
};
#endif