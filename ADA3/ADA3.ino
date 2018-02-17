#define A 8
#define B 9
#define C 10
#define D 11

#define b 4
#define c 5
#define d 6
#define f 7

#define NIBBLE_LENGTH 4
#define MAP_SIZE 16

bool stopper = false;

int mapper[][NIBBLE_LENGTH] = {
            {LOW, LOW, LOW, LOW}, // 0
            {LOW, LOW, LOW, HIGH}, // 1
            {LOW, LOW, HIGH, LOW}, // 2
            {LOW, LOW, HIGH, HIGH}, // 3
            {LOW, HIGH, LOW, LOW}, // 4
            {LOW, HIGH, LOW, HIGH}, // 5
            {LOW, HIGH, HIGH, LOW}, // 6
            {LOW, HIGH, HIGH, HIGH}, // 7
            {HIGH, LOW, LOW, LOW}, // 8
            {HIGH, LOW, LOW, HIGH}, // 9
            {HIGH, LOW, LOW, LOW}, // A
            {LOW, HIGH, HIGH, LOW}, // b
            {LOW, LOW, LOW, LOW}, // C
            {HIGH, LOW, LOW, LOW}, // d
            {HIGH, LOW, LOW, LOW}, // E
            {HIGH, LOW, LOW, LOW} // F
};

int andMapper[][NIBBLE_LENGTH] = {
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {HIGH, HIGH, HIGH, HIGH}, // 9
  {HIGH, HIGH, LOW, HIGH},
  {HIGH, HIGH, HIGH, HIGH},
  {LOW, LOW, HIGH, HIGH},
  {HIGH, HIGH, HIGH, LOW}, // d
  {LOW, LOW, HIGH, HIGH},
  {LOW, LOW, LOW, HIGH}
};

void setup() {
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(f, OUTPUT);

  attachInterrupt(0,botonFunction,CHANGE);
}

void botonFunction(){
  stopper = true;
}

void loop() {

  for(int x=0; x<MAP_SIZE; x++){

    while(stopper){}

    for(int y=0; y<NIBBLE_LENGTH; y++){ 
       
      digitalWrite(D-y, mapper[x][y]);
    }

    for(int y=0; y<NIBBLE_LENGTH; y++){

      digitalWrite(b+y, andMapper[x][y]);
    }

    delay(1000);
  }

}
