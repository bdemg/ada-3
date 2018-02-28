#include <LiquidCrystal.h>
#include <Keypad.h>

#define LCD_ROW_LENGTH 16

const byte filas = 2;
const byte columnas = 4;

char teclado [filas][columnas] ={
  {'1', '2', '3', '4'},
  {'5', '0', '0', '0'}
};

byte filapin [filas] = {13, 12};
byte colupin [columnas] = {11, 10, 9, 8};

Keypad miteclado = Keypad(makeKeymap(teclado), filapin, colupin, filas, columnas);

// rs: the number of the Arduino pin that is connected to the RS pin on the LCD
// enable: the number of the Arduino pin that is connected to the enable pin on the LCD
// d4, d5, d6, d7: the numbers of the Arduino pins that are connected to the corresponding data pins on the LCD.
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte animatePartOne[8]={
B00000,
B00000,
B00000,
B00000,
B00000,
B11111,
B11111,
B11111,
};

byte animatePartTwo[8]={
B00000,
B00000,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
};

byte animatePartThree[8]={
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
B11111,
};

void setup() {
  
  Serial.begin(9600);
  lcd.begin(LCD_ROW_LENGTH, 2);

  lcd.createChar(1,animatePartOne);
  lcd.createChar(2,animatePartTwo);
  lcd.createChar(3,animatePartThree);
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
 cleanLCD(0);
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
      cleanLCD(1);//llenar un 0% de la parte de abajo (si nos da tiempo, no se pide)
      break;
      
      default:
      return;
      break;
  }
  
  Serial.println(tecla);
}

void fillAnimation(int fillGrade){

  // lcd.setCursor(col, row);

  if(fillGrade >= 4){

    // Imprime las tres animaciones en la fila de abajo.
    for(int i = 0; i < 3; i++){
      lcd.setCursor(0,1);
      for(int j = 0; j < LCD_ROW_LENGTH; j++){
        lcd.write(i+1);
      }
      delay(300);
    }

    // Imprime la animación correspondiente en la fila de arriba.
    for(int i = 0; i < (fillGrade - 4); i++){
      lcd.setCursor(0,0);
      for(int j = 0; j < LCD_ROW_LENGTH; j++){
        lcd.write(i+1);
      }
      delay(300);
    }
    
  }
  else{

    // Imprime la animación correspondiente en la fila de abajo
    for(int i = 0; i < fillGrade; i++){
      lcd.setCursor(0,1);
      for(int j = 0; j < LCD_ROW_LENGTH; j++){
        //imprimir 16 veces el caracters
        lcd.write(i+1);
      }
      delay(300);
    }
  }
  
}

void cleanLCD(int line){
 
 lcd.setCursor(0, line);
 for(int j = 0; j < LCD_ROW_LENGTH; j++){
      lcd.print(" ");
    }
}
