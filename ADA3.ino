#define a 7
#define b 8
#define c 9
#define d 10
#define e 11
#define f 12
#define g 13

#define SEGMENT_LENGTH 7
#define MAP_SIZE 16

int mapper[][SEGMENT_LENGTH] = {
            {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW}, //0
            {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW}, //1
            {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH}, //2
            {}, //3
            {}, //4
            {}, //5
            {}, //6
            {}, //7
            {}, //8
            {}, //9
            {}, //A
            {}, //b
            {}, //C
            {}, //d
            {}, //E
            {}, //F
};

void setup() {

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {

  for(int x=0; x<MAP_SIZE; x++){

    for(int y=0; y<SEGMENT_LENGTH; y++){

      digitalWrite(a+y, mapper[x][y]);
    }

    delay(1000);
  }

}
