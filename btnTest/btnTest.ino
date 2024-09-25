int btnPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
    int resposta = digitalRead(btnPin);
    if (resposta == LOW){
    Serial.println("Está baixo");
  }

}