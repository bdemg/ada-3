#include <Keypad.h>

#include "tones.h"

#define BUZZER_PIN 3

int levelsToneLength[] = {3, 4, 5};

char levelOneTones[3];
char levelTwoTones[4];
char levelThreeTones[5];

char *levelTones[] = {levelOneTones, levelTwoTones, levelThreeTones};

int currentLevel;

bool hasPlayedLevelNotes = false;

const byte filas = 4;
const byte columnas = 4;

char teclado [filas][columnas] ={
  {NOTE_C1, NOTE_D1, NOTE_E1, NOTE_F1},
  {NOTE_G1, NOTE_A1, NOTE_AS1, NOTE_B1},
  {NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2},
  {NOTE_G2, NOTE_A2, NOTE_AS2, NOTE_B2}
};

byte filapin [filas] = {13, 12, 11, 10};
byte colupin [columnas] = {9, 8, 7, 6};

Keypad miteclado = Keypad(makeKeymap(teclado), filapin, colupin, filas, columnas);

void setup() {
  loadTones();
  currentLevel = 0;
}

void loadTones(){
  //Leer de la EEPROM los tonos y ponerlo en los arreglos
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

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
