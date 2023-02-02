#include "DHT.h"
#include "moisture.h"
#include "light.h"


#define dhtPin 8
#define dhtType DHT22

DHT dht(dhtPin, dhtType);

void setup() {
	Serial.begin(9600);
	dht.begin();
}

unsigned long previousMillis {0};
unsigned long currentMillis {0};

void loop() {
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= 2000) {
		float h = dht.readHumidity();
		float t = dht.readTemperature();

		Serial.print("Temperature = ");
		Serial.print(t);
		Serial.println(" C");
		Serial.print("Humidity = ");
		Serial.print(h);
		Serial.println(" % ");
		Serial.println("");

		previousMillis = currentMillis;
	}

}
