void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  int sensorRead = analogRead(A0);

  digitalWrite(12,HIGH);

  delay(sensorRead);

  digitalWrite(12,LOW);

  delay(sensorRead);

  Serial.println(sensorRead);
  
  delay(1);

}
