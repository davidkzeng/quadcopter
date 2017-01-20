void updateValues() {  
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
}

void getAngle() {

  if((values[0] + values[1] + values[2] + values[3]) >= 3) {
    angle = -1;
  }

  if(values[0] == 1 && values[1] == 1) {
    angle = 0;
  }
  if(values[1] == 1 && values[2] == 1) {
    angle = 90;
  }
  if(values[2] == 1 && values[3] == 1) {
    angle = 180;
  }
  if(values[3] == 1 && values[0] == 1) {
    angle = 270;
  }
  if(values[0] == 1) {
    angle = 315;
  }
  if(values[1] == 1) {
    angle = 45;
  }
  if(values[2] == 1) {
    angle = 135;
  }
  if(values[3] == 1) {
    angle = 225;
  }

  values[0] = 0;
  values[1] = 0;
  values[2] = 0;
  values[3] = 0;

}

