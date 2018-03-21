#include <EEPROM.h>
#include "tones.h"

void setup() {
    //Escribir tonos primer nivel
    EEPROM.put(0, NOTE_D1);
    EEPROM.put(1, NOTE_A1);
    EEPROM.put(2, NOTE_D2);
    
    //Escribir tonos segundo nivel
    EEPROM.put(3, NOTE_G1);
    EEPROM.put(4, NOTE_D2);
    EEPROM.put(5, NOTE_AS1);
    EEPROM.put(6, NOTE_F2);
    
    //Escribir tonos tercer nivel
    EEPROM.put(7, NOTE_C1);
    EEPROM.put(8, NOTE_A1);
    EEPROM.put(9, NOTE_D2);
    EEPROM.put(10, NOTE_G2);
    EEPROM.put(11, NOTE_E2);
}


void loop() {
  
}
