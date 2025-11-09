#include "Brake.h"

Brake::Brake(){
    this->brakePressed = false;

}

bool Brake::getBrakePressed() const {
    return brakePressed;
}

void Brake::setBrakePressed(bool brakeStatus){
    this->brakePressed = brakeStatus;
}
