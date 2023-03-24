#include <Arduino.h>
#include "light.h"

int LIGHT::getIntensity(){
    return analogRead(ldrPin);
}

bool LIGHT::create(int ldrPIN){
    ldrPin = ldrPIN;
    pinMode(ldrPin, INPUT);

    return true;
}