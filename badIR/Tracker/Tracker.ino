#include <Timer.h>

int IRR1 = 10;
int IRR2 = 11;
int IRR3 = 12;
int IRR4 = 13;
int values[4];
int rx[4];
Timer t;

void setup() {
  pinMode(IRR1, INPUT);
  pinMode(IRR2, INPUT);
  pinMode(IRR3, INPUT);
  pinMode(IRR4, INPUT);
  Serial.begin(9600);

  t.every(100, printReading);
}

void loop() {  
  if(digitalRead(IRR1) == LOW) {
    //Serial.println("Pin 1");
    values[0] = 1;
  }
  if(digitalRead(IRR2) == LOW) {
    //Serial.println("Pin 2");
    values[1] = 1;
  }
  if(digitalRead(IRR3) == LOW) {
    //Serial.println("Pin 3");
    values[2] = 1;
  }
  if(digitalRead(IRR4) == LOW) {
    //Serial.println("Pin 4");
    values[3] = 1;
  }

  t.update();
}

void printReading() {
  Serial.println("Pin 1: " + String(values[0]) + "\t" + 
                 "Pin 2: " + String(values[1]) + "\t" +
                 "Pin 3: " + String(values[2]) + "\t" +
                 "Pin 4: " + String(values[3]));


  if((values[0] + values[1] + values[2] + values[3]) >= 3) {
    
  }

  if(values[0] == 1 && values[1] == 1) {
    
  }
  if(values[1] == 1 && values[2] == 1) {
    
  }
  if(values[2] == 1 && values[3] == 1) {
    
  }
  if(values[3] == 1 && values[0] == 1) {
    
  }
  if(values[0] == 1) {
    
  }
  if(values[1] == 1) {
    
  }
  if(values[2] == 1) {
    
  }
  if(values[3] == 1) {
    
  }

  values[0] = 0;
  values[1] = 0;
  values[2] = 0;
  values[3] = 0;

}

