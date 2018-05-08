#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <Servo.h>

#define RST_PIN  9 
#define SS_PIN  10

#define PSWRD_LEN 4
#define KEYPAD_LED A0
#define ACCESS_LED A1

MFRC522 hola(SS_PIN, RST_PIN);

//-----------------------------------
//Variables para control lógico
int passwordLength = PSWRD_LEN;
char passwordInputs[PSWRD_LEN];
char storedPassword[PSWRD_LEN];
bool hasCardBeenRead;
bool watingForPassword;
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

byte colupin [columnas] = {6, 7, 8}; //CAMBIAR
byte filapin [filas] = {2, 3, 4, 5}; //CAMBIAR

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
  
  hasCardBeenRead = false;
  watingForPassword = false;
  passwordInputsCount = 0;
  loadPassword();

  servo.attach(A2);
  pinMode(KEYPAD_LED, OUTPUT);
  pinMode(ACCESS_LED, OUTPUT);
}

void loop() {

  if(!hasCardBeenRead){

    readCard();
  } else if(watingForPassword){

    readKeypad();
  } else {

    char tecla = miteclado.getKey();
    if(tecla == '*'){
      
      resetSystem();
    }    
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
       
        digitalWrite(KEYPAD_LED, HIGH);
        watingForPassword = true;
        hasCardBeenRead = true;
        Serial.println("Tarjeta reconocida");
      } else {
        
        Serial.println("Tarjeta rechazada");
        informWrongCredentials();
      }
      Serial.println();
      hola.PICC_HaltA();
    }
  }
}

void readKeypad(){

  char tecla = miteclado.getKey();
  
  if(tecla != '\0'){
    Serial.println(tecla);
    if(tecla == '*'){
      
      resetSystem();
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

      //Permitir acceso
      servo.write(178);
      digitalWrite(ACCESS_LED, HIGH);
      watingForPassword = false;
  } else{

     //informar de contraseña errónea
     informWrongCredentials();
     //poner el sistema en el estado inicial
     resetSystem();
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

void informWrongCredentials(){

  //Flashear los leds de manera intercalada (uno si y uno no) por un segundo

  for(int i=0; i<3; i++){
    digitalWrite(ACCESS_LED, HIGH);
    digitalWrite(KEYPAD_LED, LOW);
    delay(200);
    digitalWrite(ACCESS_LED, LOW);
    digitalWrite(KEYPAD_LED, HIGH);
    delay(200);
  }
}

void resetSystem(){
      
      hasCardBeenRead = false;
      watingForPassword = false;
      passwordInputsCount = 0;
      digitalWrite(KEYPAD_LED, LOW);
      digitalWrite(ACCESS_LED, LOW);
      servo.write(2);
}


