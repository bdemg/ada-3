#include <LiquidCrystal.h>
#include <Keypad.h>

const byte filas = 2;
const byte columnas = 4;

char teclado [filas][columnas] ={
  {'1', '2', '3', '4'},
  {'5', '0', '0', '0'}
};

byte filapin [filas] = {13, 12};
byte colupin [columnas] = {11, 10, 9, 8};

Keypad miteclado = Keypad(makeKeymap(teclado), filapin, colupin, filas, columnas);


const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  
  Serial.begin(9600);
  lcd.begin(16, 2);
}


void loop() {
  
  String pcMessage = Serial.readString();
  if(pcMessage != ""){
    printPcMessage(pcMessage);
  }
  
  char tecla = miteclado.getKey();
  handlePressedKey(tecla);
  
}

void printPcMessage(String message){
   
 Serial.println(message);
 lcd.setCursor(0, 0);
 lcd.print(message);
}

void handlePressedKey(char tecla){
  
  switch(tecla){
    
      case '1':
      //llenar un 20% de la parte de abajo
      break;
      
      case '2':
      //llenar un 40% de la parte de abajo
      break;
      
      case '3':
      //llenar un 60% de la parte de abajo
      break;
      
      case '4':
      //llenar un 80% de la parte de abajo
      break;
      
      case '5':
      //llenar un 100% de la parte de abajo
      break;
      
      case '0':
      //llenar un 0% de la parte de abajo (si nos da tiempo, no se pide)
      break;
      
      default:
      return;
      break;
  }
  
  Serial.println(tecla);
}

void fillAnimation(int fillGrade){
  
  lcd.setCursor(0, 1);
  
  for(int i = 0; i < fillGrade; i++){
    for(int j = 0; j < 16; j++){
      //imprimir 16 veces el caracter
    }
    delay(300);
  }
}
