uint16_t value;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(460800);

}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(A0);

  Serial.write((value >> 8) & 0xFF);
  Serial.write(value & 0xFF);


}
