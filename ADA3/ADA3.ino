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
            {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW}, //1
            {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH}, //2
            {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH}, //3
            {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH}, //4
            {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH}, //5
            {LOW, LOW, HIGH, HIGH, HIGH, HIGH, HIGH}, //6
            {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW}, //7
            {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, //8
            {HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH}, //9
            {LOW, LOW, LOW, HIGH, HIGH, LOW, HIGH}, //A 10
            {LOW, LOW, HIGH, HIGH, LOW, LOW, HIGH}, //B 11
            {LOW, HIGH, LOW, LOW, LOW, HIGH, HIGH}, //C 12
            {HIGH, LOW, LOW, HIGH, LOW, HIGH, HIGH}, //D 13
            {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH}, //E 14
            {LOW, LOW, LOW, LOW, LOW, LOW, LOW}, //F 15
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
