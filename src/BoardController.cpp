#include "BoardController.h"

BoardController::BoardController() {
  currentDeviceCount = 0;
  apiSink = nullptr;
}

int BoardController::registerController(DeviceController *controller) {
  if ( currentDeviceCount >= MAX_DEVICES ) {
    return -1;
  }
  registeredControllers[currentDeviceCount] = controller;

  if (this->apiSink != nullptr) {
    registeredControllers[currentDeviceCount]->setApiSink(this->apiSink);
  }

  return ++ currentDeviceCount;
}

void BoardController::tick(){
    std::string buff;
    for(int i = 0; i <= (currentDeviceCount - 1); i++){
        buff = "ticking device #" + std::to_string(i);
        logger->logDebug(buff.c_str());
        registeredControllers[i]->tick();
    }
}

void BoardController::setLogger(Logger *l) {
  this->logger = l;
}

void BoardController::setApiSink(APIClient *sink) {
  this->apiSink = sink;
}