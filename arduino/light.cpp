#include "light.h"
#include <Arduino.h>
int LIGHT::getIntensity(){
    return analogRead(7);
}
