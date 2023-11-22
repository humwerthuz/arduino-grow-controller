#include "TimedRelayController.h"
#include "constants.h"

TimedRelayController::TimedRelayController(uint8_t relayPin, DS3231 *clock){
	this->_relayPin = relayPin;
	this->_clock = clock;
	this->setDeviceName("TimedRelay");
	pinMode(this->_relayPin, OUTPUT);
	this->_lastState = LOW;
	digitalWrite(this->_relayPin, this->_lastState);
}

void TimedRelayController::setStartTime(uint8_t hh, uint8_t mm) {
	this->_startHH = hh;
	this->_startMM = mm;
}

void TimedRelayController::setStopTime(uint8_t hh, uint8_t mm) {
	this->_stopHH = hh;
	this->_stopMM = mm;
}

bool TimedRelayController::isTimeInRange() {
    // Extract hours and minutes
    bool is12HMode = false;
    uint8_t currentHH = this->_clock->getHour(is12HMode, is12HMode);
    uint8_t currentMM = this->_clock->getMinute();

    // Check if current time is within the specified range
    if (currentHH > _startHH || (currentHH == _startHH && currentMM >= _startMM)) {
        if (currentHH < _stopHH || (currentHH == _stopHH && currentMM <= _stopMM)) {
            return true; // Current time is within the range
        }
    }
    return false; // Current time is outside the range
}

void TimedRelayController::tick(){
	bool is12HMode = false;
	uint8_t nowHH = this->_clock->getHour(is12HMode, is12HMode);
	uint8_t nowMM = this->_clock->getMinute();
	if ( this->logger != nullptr ) {
        std::string b = "Device " + std::string(this->getDeviceName()) + " got reading " + std::to_string(nowHH)
                + ":" + std::to_string(nowMM);
		this->logger->logInfo(b.c_str());
	}
	bool isTimeInRange = this->isTimeInRange();
	if ( isTimeInRange && this->_lastState != HIGH ) {
		this->logger->logInfo("turning relay on");
		digitalWrite(this->_relayPin, HIGH);
		this->_lastState = HIGH;
		if ( this->apiSink != nullptr ) this->sinkData(TagRelayEvent, TagOn, this->getDeviceName());
	} else if ( !isTimeInRange && this->_lastState != LOW ) {
		this->logger->logInfo("turning relay off");
		digitalWrite(this->_relayPin, LOW);
		this->_lastState = LOW;
		if ( this->apiSink != nullptr ) this->sinkData(TagRelayEvent, TagOff, this->getDeviceName());
	}
}