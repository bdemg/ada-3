#include <EEPROM.h>

void setup() {
    //Escribir tonos primer nivel
    EEPROM.put(0, '4');
    EEPROM.put(1, '7');
    EEPROM.put(2, '0');
    EEPROM.put(3, '1');
}


void loop() {
  
}
