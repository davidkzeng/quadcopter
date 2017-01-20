int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(10);
  digitalWrite(LED, LOW);
  delay(10);
}
