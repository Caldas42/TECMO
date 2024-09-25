int buzzerPin = 7;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  playErrorTone(buzzerPin);  // Play an error tone sequence

  //playRightTone(buzzerPin);  // Play a correct answer tone sequence
}

// Function to play an error tone
void playErrorTone(int buzzerPin) {
  tone(buzzerPin, 100, 500);  // Generate a 100 Hz tone for 500 milliseconds
  delay(500);                 // Wait for 500 milliseconds
  noTone(buzzerPin);          // Stop the tone
}

// Function to play a correct answer tone sequence
void playRightTone(int buzzerPin) {
  tone(buzzerPin, 784);   // Play a 784 Hz tone (G5)
  delay(150);             // Wait for 150 milliseconds

  tone(buzzerPin, 1047);  // Play a 1047 Hz tone (C6)
  delay(150);             // Wait for 150 milliseconds

  tone(buzzerPin, 1318);  // Play a 1318 Hz tone (E6)
  delay(150);             // Wait for 150 milliseconds

  tone(buzzerPin, 1568);  // Play a 1568 Hz tone (G6)
  delay(150);             // Wait for 150 milliseconds

  noTone(buzzerPin);      // Stop the tone
}
