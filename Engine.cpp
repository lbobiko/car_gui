#include "Engine.h"

Engine::Engine() {
    this->engineStatus = false;
}

bool Engine::getEngineStatus(){
    return engineStatus;
}

void Engine::setEngineStatus(bool status){
    this->engineStatus = status;
}
