uint16_t counter;
uint16_t output;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (counter == 500) {
    counter = 0;
  }
  if (counter >= 250) {
    output = 500;
  }
  else {
    output = 0;
    }
  Serial.write((counter >> 8) & 0xFF);
  Serial.write(counter & 0xFF);
  counter++;

}
