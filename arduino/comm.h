#include <ArduinoBLE.h>

class COMMS {

  public:
    BLEIntCharacteristic switchCharacteristic{"2A57", BLERead | BLEWrite};
    BLEDevice central;
    
    void create(char name[10]);

    void connect();

    void sendMsg(uint32_t msg);

    void readMsg(uint32_t& msg);
};
