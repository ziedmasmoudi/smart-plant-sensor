//#define TEST
#ifdef TEST
#include "./tests/tests.cpp"
#endif
#ifndef TEST

#include <Arduino.h>
#include "DHT.h"
#include "moisture.h"
#include "light.h"
#include "comm.h"
#include <math.h>

#define dhtPin 8
#define dhtType DHT22
#define soilSignalPin A6
#define soilPowerPin 19

DHT dht(dhtPin, dhtType);
COMMS Comms; 
LIGHT Light;
MOISTURE Moisture;

void setup() {
	Serial.begin(9600);

	dht.begin();

  Comms.create("aaa");
  Moisture.create(soilPowerPin, soilSignalPin);

}

unsigned long previousMillis {0};
unsigned long currentMillis {0};

void loop() {
	if (!Comms.isConnected()){
		Comms.connect();
	}


  
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= 2000) {
		int h = round(dht.readHumidity()*100);
		int t = round(dht.readTemperature()*100);
		int l = Light.getIntensity();
    int m = Moisture.getValue();

		Serial.print("Temperature = ");
		Serial.print(t);
		Serial.println(" C");
		Serial.print("Humidity = ");
		Serial.print(h);
		Serial.println(" % ");
		Serial.print("Light Intensity = ");
		Serial.println(l);
    Serial.print("Soil moisture = ");
    Serial.println(m);
		Serial.println("");

    Comms.sendMsg(charId::temp, t);
		Comms.sendMsg(charId::humidity, h);
		Comms.sendMsg(charId::light, l);
    Comms.sendMsg(charId::moisture, m);

		previousMillis = currentMillis;
	}

}
#endif
