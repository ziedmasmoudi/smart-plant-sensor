//based on code from https://docs.arduino.cc/tutorials/nano-33-iot/bluetooth by Fabricio Troya

#include <ArduinoBLE.h>
#include "comm.h"

int buttonState = 0;

bool COMMS::create(char name[10]) {
  BLEService sensorService("180A"); // BLE LED Service

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName(name);
  BLE.setAdvertisedService(sensorService);

  // add the characteristics to the service
  for (int i = 0; i < charId::count; i++){
    sensorService.addCharacteristic(characteristics[i]);
  }

  // add service
  BLE.addService(sensorService);

  // set the initial value for the characteristics:
  for (int i = 0; i < charId::count; i++){
    characteristics[i].writeValue(0);
  }

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");

  return true;
}

void COMMS::connect() {
  // listen for BLE peripherals to connect:
  COMMS::central = BLE.central();

  // if a central is connected to peripheral:
  if (COMMS::central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(COMMS::central.address());
  }
}

void COMMS::sendMsg(charId characteristic, uint32_t msg) {
  // if a central is connected to peripheral:
  if (central.connected()) {
    characteristics[characteristic].writeValue(msg);
  }
}

void COMMS::readMsg(charId characteristic, uint32_t& msg) {
  // if a central is connected to peripheral:
  if (central.connected()) {
    characteristics[characteristic].readValue(msg);
  }
}
