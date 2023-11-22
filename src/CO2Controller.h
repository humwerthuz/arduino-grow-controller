#ifndef	CO2_CONTROLLER_H
#define CO2_CONTROLLER_H

#define ZH_BAUDRATE 9600

#include "DeviceController.h"
#include <MHZ19.h>
#include <HardwareSerial.h>

class CO2Controller : public DeviceController {
private:
    bool initialized{false};
	int8_t txPin{};
	int8_t rxPin{};
    HardwareSerial *serialPort{};
	int8_t co2ValveRelayPin{};
	uint32_t ticksCount;
	int _startCO2{};
	int _stopCO2{};
	MHZ19 *mhz19;
public:
	CO2Controller(int8_t tp, int8_t rp, int uart_nr, int8_t valvePin);
	void setCO2Range(int, int);
	void init();
	void tick() override;
};
#endif