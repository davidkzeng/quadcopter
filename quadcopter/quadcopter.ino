#include <Servo.h>

#define PIN_MOTOR0 6
#define PIN_MOTOR1 7
#define PIN_MOTOR2 8
#define PIN_MOTOR3 9

Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;

int value = 0;

void setup() {
  Serial.begin(9600);

  motor0.attach(PIN_MOTOR0, 1000, 2000);
  motor1.attach(PIN_MOTOR1, 1000, 2000);
  motor2.attach(PIN_MOTOR2, 1000, 2000);
  motor3.attach(PIN_MOTOR3, 1000, 2000);
}

void loop() {
  //Serial.println("lol2");
  motor0.write(value);
  motor1.write(value);
  motor2.write(value);
  motor3.write(value);
  //value = Serial.parseInt();
  
  if(Serial.available()) {
    value = Serial.parseInt();
    Serial.println(value);
  } 
  //Serial.println(value);
  //delay(1000);  
}
