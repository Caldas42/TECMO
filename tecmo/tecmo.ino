#include <Wire.h>                  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>      // Include the library for the I2C LCD display

LiquidCrystal_I2C lcd(0x27, 20, 4); // Set LCD I2C address and screen size (20 columns, 4 rows)

// Button pins for difficulty selection
const int greenBtnPin = 4;
const int yellowBtnPin = 3;
const int redBtnPin = 2;

int difficulty;                    // Variable to store selected difficulty level

// Constants representing the number of blocks, levels, and questions
const int blocks = 5;
const int levels = 3;
const int questions = 1;

// Array storing the question strings for each block and difficulty level
char* perguntas[blocks][levels][questions] =

                                  {{{"Qual peca transforma a energia da tomada para o computador?"},    // Easy Power supply questions
                                    {"Qual peca converte a corrente alternada (AC) em corrente continua (DC)?"},    // Normal Power supply questions
                                    {"Qual peca possui conectores 24 pinos e 8 pinos?"}},   // Hard Power supply questions

                                   {{"Qual peca e o cerebro do computador?"},    // Easy CPU questions
                                    {"Qual peca e a unidade central de processamento?"},    // Normal CPU questions
                                    {"Qual peca usa arquitetura como x86 ou ARM?"}},   // Hard CPU questions
                                    
                                    {{"Qual peca armazena  temporariamente os dados em uso pelo computador?"},   // Easy RAM questions
                                     {"Qual peca e volatil e perde dados ao desligar o PC?"},   // Normal RAM questions
                                     {"Qual peca pode utilizar a tecnologia DDR (Double Data Rate) para aumentar a largura de banda?"}},  // Hard RAM questions
                                     
                                    {{"Qual a peca que oferece maior velocidade de leitura e escrita em comparacao com os HDs?"},   // Easy SSD questions
                                     {"Qual peca pode ter formato M.2, U.2, ou 2.5?"},   // Normal SSD questions
                                     {"Qual peca usa NAND types como SLC, MLC, TLC, QLC?"}},  // Hard SSD questions
                                     
                                    {{"Qual peca e responsavel pelo processamento grafico?"}, // Easy GPU questions
                                     {"Qual componente e projetado para suportar a execucao de APIs de graficos?"}, // Normal GPU questions
                                     {"Qual unidade suporta APIs graficas como DirectX e OpenGL?"}}}; // Hard GPU questions

// Array for reed switch pins
int reedSwitches[5] = {8, 12, 11, 10, 9}; // 8 - PS, 9 - gpu, 10 - ssd, 11 - ram, 12 - cpu

// LED pin constants
const int redLedPin = 6;
const int greenLedPin = 5;

// Buzzer pin
int buzzerPin = 7;

void setup() {
  Serial.begin(9600);
  lcd.init();                 // Initialize the LCD
  lcd.backlight();            // Turn on the LCD backlight

  // Set button pins as input with pull-up resistors
  pinMode(greenBtnPin, INPUT_PULLUP);
  pinMode(yellowBtnPin, INPUT_PULLUP);
  pinMode(redBtnPin, INPUT_PULLUP);

  // Initialize reed switches as inputs with pull-up resistors
  for (int i = 0; i < 5; i++) {
    pinMode(reedSwitches[i], INPUT_PULLUP);
  }

  // Set LED pins as outputs
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  lcd.clear();                // Clear the LCD
  int cont = 0;               // Variable to track the current block

  // Display instructions for difficulty selection
  lcd.setCursor(5, 0);
  lcd.print("Selecione");

  lcd.setCursor(9, 1);
  lcd.print("a");

  lcd.setCursor(4, 2);
  lcd.print("dificuldade");

  // Call function to set difficulty based on button input
  difficulty = setDifficulty(greenBtnPin, yellowBtnPin, redBtnPin);

  
  // Arrays to store the random order of blocks and questions
  int questionsArray[questions];
  int blocksOrder[blocks]; // 0 - 8 (PS), 1 - 9 (GPU)

  randomSeed(analogRead(0));   // Generate a random seed based on analog pin 0

  randomBlocksOrder(blocksOrder, blocks); // Generate a random order for blocks
  randomQuestions(questionsArray, questions); // Generate a random order for questions
  int blocksFitted[blocks] = {-1, -1, -1, -1, -1};

  // Loop through each block (5 blocks)
  for (int j = 0; j < blocks; j++) {
    lcd.clear();
    lcd.setCursor(0, 0);

    // Display the question for the selected difficulty and block
    lcd.print(perguntas[blocksOrder[j]][difficulty][questionsArray[j]]);

    int contBreak = 0;          // Variable to exit the inner loop

    // Wait for the correct reed switch input
    while (true) {
      for (int k = 0; k < blocks; k++) {
        bool blockFitted = false;

        for (int l = 0; l < blocks; l++) {
          if (blocksFitted[l] == k) {
            blockFitted = true;
            break;
          }
        }

        if (k == blocksOrder[j] && digitalRead(reedSwitches[blocksOrder[j]]) == LOW) {
          digitalWrite(greenLedPin, HIGH);   // Turn on green LED for correct input
          playRightTone(buzzerPin);          // Play correct tone
          digitalWrite(greenLedPin, LOW);    // Turn off green LED

          blocksFitted[j] = k;
          contBreak += 1;

          break;
        } else if (blockFitted == false && digitalRead(reedSwitches[k]) == LOW) {
          digitalWrite(redLedPin, HIGH);       // Turn on red LED for wrong input
          playErrorTone(buzzerPin);            // Play error tone
          digitalWrite(redLedPin, LOW);        // Turn off red LED
        }
      }

      if (contBreak != 0) {
        break;  // Exit inner loop when correct switch is pressed
      }
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Obrigado por jogar!");
  delay(2000);
}

// Function to set difficulty level based on button input
int setDifficulty(int btn1, int btn2, int btn3) {
  while (true) {
    if (digitalRead(btn1) == LOW) {
      return 0;  // Easy difficulty
    } else if (digitalRead(btn2) == LOW) {
      return 1;  // Normal difficulty
    } else if (digitalRead(btn3) == LOW) {
      return 2;  // Hard difficulty
    }
  }
}

// Function to generate random order for blocks
void randomBlocksOrder(int array[], int length) {
  int cont = 0;

  while (cont < length) {
    bool alreadyIn = false;
    int randomNum = rand() % length;

    // Check if the number is already in the array
    for (int i = 0; i < cont; i++) {
      if (array[i] == randomNum) {
        alreadyIn = true;
        break;
      }
    }

    // If the number is not already in the array, add it
    if (!alreadyIn) {
      array[cont] = randomNum;
      cont++;
    }
  }
}

// Function to generate random questions order
void randomQuestions(int array[], int length) {
  for (int i = 0; i < length; i++) {
    array[i] = rand() % length;
  }
}

// Function to play the correct tone sequence
void playRightTone(int buzzerPin) {
  tone(buzzerPin, 784);
  delay(150);

  tone(buzzerPin, 1047);
  delay(150);

  tone(buzzerPin, 1318);
  delay(150);

  tone(buzzerPin, 1568);
  delay(150);

  noTone(buzzerPin);
}

// Function to play the error tone
void playErrorTone(int buzzerPin) {
  tone(buzzerPin, 100, 500);
  delay(500);
  noTone(buzzerPin);
}
