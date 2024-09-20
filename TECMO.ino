#include <Wire.h>                  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>     // Include the LiquidCrystal_I2C library for the LCD display

LiquidCrystal_I2C lcd(0x27, 20, 4); // Initialize the LCD object with the I2C address (0x27), 20 columns, and 4 rows

const int greenBtn = 6;
const int yellowBtn = 4;
const int redBtn = 5;

int difficulty;

char* easyQuestions[5] = {"Qual peca armazena dados temporariamente", "Qual e o cerebro do computador", "Qual peca armazena dados permanentemente", "Qual peca processa graficos e imagens", "Qual peca fornece energia ao computador."};
char* normalQuestions[5] = {"Qual peca tem frequencias e latencias", "Qual executa varias tarefas simultaneas", "Qual peca usa memoria flash", "Qual peca acelera a criacao de imagens", "Qual peca converte energia eletrica"};
char* hardQuestions[5] = {"Qual peca pode ser DDR3, DDR4 ou DDR5", "Qual peca usa arquiteturas x86 ou ARM", "Qual peca usa SATA, NVMe ou PCIe", "Qual peca suporta Ray Tracing e DLSS", "Qual tem certificacoes de eficiencia"};

int reedSwitches[3] = {8, 10, 9};

const int redLed = 2;
const int greenLed = 3;

int buzzerPin = 7;

int cont;
int contBreak;

void setup() {
  pinMode(greenBtn, INPUT_PULLUP);
  pinMode(yellowBtn, INPUT_PULLUP);
  pinMode(redBtn, INPUT_PULLUP);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(reedSwitches[i], INPUT_PULLUP);
  }

  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the backlight
}

void loop() {
  lcd.clear();           // Clear any previous content displayed on the LCD
  cont = 0;

  lcd.setCursor(5, 0);
  lcd.print("Selecione");

  lcd.setCursor(9, 1);
  lcd.print("a");

  lcd.setCursor(4, 2);
  lcd.print("dificuldade");

  while (true) {
    if (digitalRead(greenBtn) == LOW) {
      difficulty = 0;
      break;
    } else if (digitalRead(yellowBtn) == LOW) {
      difficulty = 1;
      break;
    } else if (digitalRead(redBtn) == LOW) {
      difficulty = 2;
      break;
    }
  }

  for (int question = 0; question < 5; question++) {
    lcd.clear(); // Clear any previous content displayed on the LCD
    lcd.setCursor(0, 0);

    if (difficulty == 0) {
      lcd.print(easyQuestions[question]);
    } else if (difficulty == 1) {
      lcd.print(normalQuestions[question]);
    } else if (difficulty == 2) {
      lcd.print(hardQuestions[question]);
    }

    contBreak = 0;

    while (true) {
      for (int socket = cont; socket < 5; socket++) {
        if (socket == question) {
          if (digitalRead(reedSwitches[question]) == LOW) {
            digitalWrite(greenLed, HIGH);
            playRightTone(buzzerPin);
            digitalWrite(greenLed, LOW);
            

            contBreak += 1;
            cont += 1;
            break;
          }
        } else if (digitalRead(reedSwitches[socket]) == LOW) {
          digitalWrite(redLed, HIGH);
          playErrorTone(buzzerPin);
          digitalWrite(redLed, LOW);
        }
      }

      if (contBreak != 0) {
        break;
      }
    }
  }
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

// Function to play an error tone
void playErrorTone(int buzzerPin) {
  tone(buzzerPin, 100, 500);  // Generate a 100 Hz tone for 500 milliseconds
  delay(500);                 // Wait for 500 milliseconds
  noTone(buzzerPin);          // Stop the tone
}
