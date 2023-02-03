#include <ArduinoBLE.h>

enum charId {temp, humidity, light,count};

class COMMS {
    

    BLEIntCharacteristic characteristics[3] = { BLEIntCharacteristic("2A57", BLERead | BLEWrite),
                                              BLEIntCharacteristic("2A58", BLERead | BLEWrite),
                                              BLEIntCharacteristic("2A59", BLERead | BLEWrite)};
      
    
    BLEDevice central;

  public:
    
    void create(char name[10]);

    void connect();

    void sendMsg(charId characteristic, uint32_t msg);

    void readMsg(charId characteristic, uint32_t& msg);

    bool isConnected(){
      return central.connected();
    }
};
