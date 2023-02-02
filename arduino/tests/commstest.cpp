#include "../comm.h"
#include <math.h>



class COMMSTEST {
  COMMS comms;

  public:
  void setup(){
    Serial.begin(9600);
    comms.create("aaa");
  }
  int msg;

  unsigned long previousMillis {0};
  unsigned long currentMillis {0};
  void loop(){ 
    if (!comms.central.connected()){
      comms.connect();
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 2000) {
      if (Serial.available() > 0) {
        int msg = Serial.readString().toInt();
        Serial.println(msg);
        comms.sendMsg(msg);
      }
      previousMillis = currentMillis;
    }
  }
};
