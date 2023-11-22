#include "CO2Controller.h"

CO2Controller::CO2Controller(int8_t tp, int8_t rp, int uart_nr, int8_t valvePin) {
    mhz19 = new MHZ19();
    ticksCount = 0;
	rxPin = tp;
    txPin = rp;
    this->serialPort = new HardwareSerial(uart_nr);
    co2ValveRelayPin = valvePin;
	pinMode(this->co2ValveRelayPin, OUTPUT);
	this->setDeviceName("CO2Controller");
}

void CO2Controller::init(){
    if(this->serialPort == nullptr) {
        log_e("SerialPort is null, CO2Controller cannot continue");
        return;
    }
    this->serialPort->begin(ZH_BAUDRATE, SERIAL_8N1, this->rxPin, this->txPin, false, 20000UL);
	this->mhz19->begin(*this->serialPort);
	this->mhz19->autoCalibration(false);
    this->initialized = true;
}

void CO2Controller::tick(){
    if(!this->initialized) {
        log_e("CO2Controller not in initialized state, cannot continue");
        return;
    }
	int co2reading = this->mhz19->getCO2();
	if ( this->logger != nullptr ) {
		char buff[64];
		snprintf(buff, sizeof(buff), "Device %s got reading %d", this->getDeviceName(), co2reading);
		this->logger->logInfo(buff);
	}
	if ( this->apiSink != nullptr ) {
		char buff[5];
		snprintf(buff, sizeof(buff), "%d", co2reading);
		this->sinkData("co2_reading", buff, this->getDeviceName());
	}
	if ( co2reading >= this->_stopCO2 ) {
		digitalWrite(this->co2ValveRelayPin, LOW);
		this->sinkData("co2_injection", "off", this->getDeviceName());
	} else if ( co2reading <= this->_startCO2 ) {
		digitalWrite(this->co2ValveRelayPin, HIGH);
		this->sinkData("co2_injection", "on", this->getDeviceName());
	}
	this->ticksCount ++;
}

void CO2Controller::setCO2Range(int startCO2, int stopCO2) {
	this->_startCO2 = startCO2;
	this->_stopCO2 = stopCO2;
}