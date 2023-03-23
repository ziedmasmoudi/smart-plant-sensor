#include "moisture.h"
#include <Arduino.h>

bool MOISTURE::create(int powerPIN, int signalPIN){
    powerPin = powerPIN;
    pinMode(powerPin, OUTPUT);
    digitalWrite(powerPin, LOW);
    
    signalPin = signalPIN;
    pinMode(signalPin, INPUT);
    
    return true;
}

int MOISTURE::getValue(){
    digitalWrite(powerPin, HIGH);
    delay(10);
    int val = analogRead(signalPin);
    digitalWrite(powerPin, LOW);
    return val;
}
