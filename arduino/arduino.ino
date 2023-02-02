//#define TEST
#ifdef TEST
#include "./tests/tests.cpp"
#endif
#ifndef TEST

#include "DHT.h"
#include "moisture.h"
#include "light.h"
#include "comm.h"
#include <math.h>

#define dhtPin 8
#define dhtType DHT22

DHT dht(dhtPin, dhtType);
COMMS comms; 

void setup() {
	Serial.begin(9600);

	dht.begin();

  	comms.create("aaa");

}

unsigned long previousMillis {0};
unsigned long currentMillis {0};

void loop() {
	if (!comms.central.connected()){
		comms.connect();
	}


  
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= 2000) {
		float h = dht.readHumidity();
		int t = round(dht.readTemperature()*100);

		Serial.print("Temperature = ");
		Serial.print(t);
		Serial.println(" C");
		Serial.print("Humidity = ");
		Serial.print(h);
		Serial.println(" % ");
		Serial.println("");
    	comms.sendMsg(t);
		previousMillis = currentMillis;
	}

}
#endif
