#include <EEPROM.h>
#include <Keypad.h>
#include <HashMap.h>
#include "tones.h"

#define BUZZER_PIN 3

//-------------------------------------
//Arreglos para cargar los tonos de cada nivel
int levelsToneLength[] = {2, 3, 4};

char levelOneTones[2];
char levelTwoTones[3];
char levelThreeTones[4];

char *levelTones[] = {levelOneTones, levelTwoTones, levelThreeTones};

//------------------------------------
//Variables para controlar el flujo del juego
int currentLevel;
bool hasPlayedLevelNotes = false;

//-----------------------------------
//Creación del teclado
const byte filas = 2;
const byte columnas = 2;

char teclado [filas][columnas] ={
  {NOTE_E2, NOTE_F2},
  {NOTE_A2, NOTE_B2}
};

byte filapin [filas] = {13, 12};
byte colupin [columnas] = {11, 10};

Keypad miteclado = Keypad(makeKeymap(teclado), filapin, colupin, filas, columnas);

//----------------------------------
//HashMap para relacionar tonos y pines donde se encuentran los leds
const byte HASH_SIZE = 5;
HashType<char,int> hashRawArray[HASH_SIZE];
HashMap<char,int> hashMap = HashMap<char,int>( hashRawArray , HASH_SIZE );

void setup() {
  loadTones();
  currentLevel = 0;

  hashMap[0](NOTE_E2,9);
  hashMap[1](NOTE_F2,8);
  hashMap[2](NOTE_A2,7);
  hashMap[3](NOTE_B2,6);
}

void loadTones(){

  int eepromAddress = 0;
  
  for(int levelCount = 0; levelCount < 3; levelCount++){
    
    for(int toneCount = 0; toneCount < levelsToneLength[levelCount]; toneCount++){
      
        levelTones[levelCount][toneCount] = EEPROM.read(eepromAddress);
        eepromAddress++;
   }  
  }
}


void loop() {

  if(!hasPlayedLevelNotes){

    playMelody(levelTones[currentLevel]);
    hasPlayedLevelNotes = true;

  }else{

    char tecla = miteclado.getKey();
    if(tecla != '\0'){
      //Hacer algo
    }
  }

}

void playMelody(char melody[]){
  
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < levelsToneLength[currentLevel]; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / 2;
    tone(BUZZER_PIN, melody[thisNote], noteDuration);

    //encender el pin correspondiente a la nota
    lightUpToneLed(melody[thisNote]);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);

    //Apagar el pin correspondiente
    turnOffToneLed(melody[thisNote]);
  }
}

void lightUpToneLed(char note){

    int ledPin = hashMap.getValueOf(note);
    digitalWrite(ledPin, HIGH);
}

void turnOffToneLed(char note){

    int ledPin = hashMap.getValueOf(note);
    digitalWrite(ledPin, LOW);
}


