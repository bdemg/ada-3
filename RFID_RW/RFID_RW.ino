#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define RST_PIN  9 
#define SS_PIN  10

MFRC522 hola(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  hola.PCD_Init();
  Serial.println("Lectura del UID");
}

void loop() {
  
  if ( hola.PICC_IsNewCardPresent()){
    
    // Read Card
    if ( hola.PICC_ReadCardSerial()){
      Serial.print("Card UID:");
      for (byte i = 0; i < hola.uid.size; i++) {
        Serial.print(hola.uid.uidByte[i] < 0 ? " 0" : " ");
        Serial.print(hola.uid.uidByte[i], HEX);

        /*if( isInMemory(hola.uid.uidByte[i], i) ){
          Serial.println("Ya está en memoria.");
        }
        else{
          Serial.println("No está en memoria. Guardando ... ");
          EEPROM.put( 10+i, hola.uid.uidByte[i] );
          Serial.println("Guardado.");
        }*/
      }

      Serial.println();
      
      if(isCardInMemory(hola.uid.uidByte, hola.uid.size)){
        Serial.println("Tarjeta ya en memoria");
      } else {
        Serial.println("Tarjeta no en memoria, guardando...");
        saveInMemory(hola.uid.uidByte, hola.uid.size);
        Serial.println("Guardado");
      }
      Serial.println();
      hola.PICC_HaltA();
    }
  }
}

bool isCardInMemory(byte cardId[], int sizeOfId){

  for (byte i = 0; i < sizeOfId; i++) {
    if(cardId[i] != EEPROM.read(10+i)){
      return false;
    }
  }
  return true;
}

void saveInMemory(byte cardId[], int sizeOfId){

  for (byte i = 0; i < sizeOfId; i++) {

    EEPROM.put( 10+i, cardId[i] );
  }
}


bool isInMemory(byte hex, int i){

  if(EEPROM.read(10+i) == hex){
    return true;
  }
  else{
    return false;
  }
  /*Serial.print(EEPROM.read(10),HEX);
  Serial.print(EEPROM.read(11),HEX);
  Serial.print(EEPROM.read(12),HEX);
  Serial.print(EEPROM.read(13),HEX);
  Serial.println();*/
}
