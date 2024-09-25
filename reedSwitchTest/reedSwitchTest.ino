const int reedSwitchPin = 2; // Pino conectado ao reed switch

void setup() {
  Serial.begin(9600);   
  pinMode(reedSwitchPin, INPUT_PULLUP); // Configura o pino como entrada com resistor de pull-up interno
}

void loop() {
  if (digitalRead(reedSwitchPin) == LOW) {
    Serial.println("Reed switch ativado!");
  }
}