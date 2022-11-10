#include "dht.h"
#include "moisture.h"
#include "light.h"


#define dhtPin 8
dht DHT;

void setup() {
	Serial.begin(9600);
}

unsigned long previousMillis {0};
unsigned long currentMillis {0};

void loop() {
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= 2000) {
		int dhtRet = DHT.read(dhtPin);

		Serial.print("Temperature = ");
		Serial.print(DHT.temperature);
		Serial.println(" C");
		Serial.print("Humidity = ");
		Serial.print(DHT.humidity);
		Serial.println(" % ");
		Serial.println("");

		previousMillis = currentMillis;
	}

}
