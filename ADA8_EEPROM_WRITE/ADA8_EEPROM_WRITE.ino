#include <EEPROM.h>
#include "tones.h"

void setup() {
    //Escribir tonos primer nivel
    EEPROM.put(0, NOTE_E2);
    EEPROM.put(1, NOTE_F2);
    
    //Escribir tonos segundo nivel
    EEPROM.put(2, NOTE_E2);
    EEPROM.put(3, NOTE_B2);
    EEPROM.put(4, NOTE_A2);
    
    //Escribir tonos tercer nivel
    EEPROM.put(5, NOTE_F2);
    EEPROM.put(6, NOTE_A2);
    EEPROM.put(7, NOTE_B2);
    EEPROM.put(8, NOTE_E2);

}


void loop() {
  
}
