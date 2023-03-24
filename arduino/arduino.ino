#include <Arduino.h>
#include <math.h>

#include "DHT.h"
#include "moisture.h"
#include "light.h"
#include "comm.h"

constexpr uint8_t dhtPin  {8};
constexpr uint8_t soilPowerPin  {19};
constexpr uint8_t soilSignalPin  {20};
constexpr uint8_t ldrPin  {7};

DHT dht(dhtPin, DHT22);
COMMS Comms; 
LIGHT Light;
MOISTURE Moisture;

void setup() {
	Serial.begin(9600);

	dht.begin();

  	Comms.create("Mirabilis");
	Light.create(ldrPin);
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

		printData(h,t,l,m);

    	Comms.sendMsg(charId::temp, t);
		Comms.sendMsg(charId::humidity, h);
		Comms.sendMsg(charId::light, l);
    	Comms.sendMsg(charId::moisture, m);

		previousMillis = currentMillis;
	}
}

void printData(int h,int t,int l,int m){
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
}