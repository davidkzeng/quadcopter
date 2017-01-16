#include <Servo.h>

#define PIN_MOTOR0 9

Servo motor0;

int value = 0;

void setup() {
  Serial.begin(9600);

  motor0.attach(PIN_MOTOR0);
}

void loop() 
  Serial.println("lol2");
  motor0.writeMicroseconds(2000);
  /* if(Serial.available()) {
    value = Serial.parseInt();
    Serial.println(value);
  } */
  delay(1000);  
}
