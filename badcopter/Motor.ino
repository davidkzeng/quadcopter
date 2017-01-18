void motorInit(){
  motor0.attach(PIN_MOTOR0, 1000, 2000);
  motor1.attach(PIN_MOTOR1, 1000, 2000);
  motor2.attach(PIN_MOTOR2, 1000, 2000);
  motor3.attach(PIN_MOTOR3, 1000, 2000);
  motor0.write(0);
  motor1.write(0);
  motor2.write(0);
  motor3.write(0);
}

void motorArm(){
  motor0.write(0);
  motor1.write(0);
  motor2.write(0);
  motor3.write(0);
}

void update_motors(int m0, int m1, int m2, int m3)
{
  motor0.write(m0);
  motor1.write(m1);
  motor2.write(m2);
  motor3.write(m3);
  Serial.print("motor: ");
  Serial.print(m0);
  Serial.print(" ");
  Serial.print(m1);
  Serial.print(" ");
  Serial.print(m2);
  Serial.print(" ");
  Serial.println(m3);
}

