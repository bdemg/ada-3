#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>

#define RST_PIN  9 
#define SS_PIN  10
#define PSWRD_LEN 4

MFRC522 hola(SS_PIN, RST_PIN);

//-----------------------------------
//Variables para control lógico
int passwordLength = PSWRD_LEN;
char passwordInputs[PSWRD_LEN];
char storedPassword[PSWRD_LEN];
bool hasCardBeenRead;
int passwordInputsCount;

//-----------------------------------
//Creación del teclado
const byte filas = 4;
const byte columnas = 3;

char teclado [filas][columnas] ={
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte colupin [columnas] = {11, 12, 13}; //CAMBIAR
byte filapin [filas] = {7, 8, 9, 10}; //CAMBIAR

Keypad miteclado = Keypad(makeKeymap(teclado), filapin, colupin, filas, columnas);
//-----------------------------------
Servo servo;


void loadPassword(){
    
  for(int charCount = 0; charCount < passwordLength; charCount++){
    
      storedPassword[charCount] = EEPROM.read(charCount);
 }  
}

void setup() {
  
  Serial.begin(9600);
  SPI.begin();
  hola.PCD_Init();
  Serial.println("Lectura del UID");
  servo.attach(5);
  hasCardBeenRead = false;
  passwordInputsCount = 0;
}

void loop() {

  if(!hasCardBeenRead){

    readCard();
  } else {

    readKeypad();
  }
  
}

void readCard(){
  if ( hola.PICC_IsNewCardPresent()){
    // Read Card
    if ( hola.PICC_ReadCardSerial()){
      Serial.print("Card UID:");
      for (byte i = 0; i < hola.uid.size; i++) {
        Serial.print(hola.uid.uidByte[i] < 0 ? " 0" : " ");
        Serial.print(hola.uid.uidByte[i], HEX);
      }

      Serial.println();
      
      if(isCardInMemory(hola.uid.uidByte, hola.uid.size)){
       
        //pasa a dejarte escribir algo en el keypad
      } else {
        
        //Mandalo a la verga morro
      }
      Serial.println();
      hola.PICC_HaltA();
    }
  }
}

void readKeypad(){

  char tecla = miteclado.getKey();
  
  if(tecla != '\0'){
    if(tecla == '*'){
      //cancelar
    } else {
      handlePasswordInput(tecla);
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

void handlePasswordInput(char key){

 if(passwordInputsCount < passwordLength){
  
    passwordInputs[passwordInputsCount] = key;
    passwordInputsCount++;
 }

 if(passwordInputsCount >= passwordLength){

    checkForCorrectPassword();
 }
}

void checkForCorrectPassword(){

  if(areInputsCorrect()){

      //mover el servo y abrir la puerta
      
      //poner el sistema en estado de espera del cierre
  } else{

     //informar de contraseña errónea

     //poner el sistema en el estado inicial
  }
}

bool areInputsCorrect(){
  
  for (int currentChar = 0; currentChar < passwordLength; currentChar++) {

    if(passwordInputs[currentChar] != storedPassword[currentChar]){
      return false;
    }
  }
  return true;
}

