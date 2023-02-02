
//based on code from https://docs.arduino.cc/tutorials/nano-33-iot/bluetooth by Fabricio Troya

#include <ArduinoBLE.h>
#include "comm.h"

int buttonState = 0;

void COMMS::create(char name[10]) {

  BLEService ledService("180A"); // BLE LED Service

  // BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
  //switchCharacteristic = switchCharacteristic("2A57", BLERead | BLEWrite);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName(name);
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characteristic:
  switchCharacteristic.writeValue(1101214515);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
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

void COMMS::sendMsg(uint32_t msg) {
  // if a central is connected to peripheral:
  if (central.connected()) {
    switchCharacteristic.writeValue(msg);
  }
}
void COMMS::readMsg(uint32_t& msg) {
  // if a central is connected to peripheral:
  if (central.connected()) {
    switchCharacteristic.readValue(msg);
  }
}
