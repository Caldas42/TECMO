#include <Wire.h>                  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>     // Include the LiquidCrystal_I2C library for the LCD display

LiquidCrystal_I2C lcd(0x27, 20, 4); // Initialize the LCD object with the I2C address (0x27), 20 columns, and 4 rows

const int greenBtnPin = 2;
const int yellowBtnPin = 3;
const int redBtnPin = 4;

srand(time(NULL));

// comeca aqui!

int quantPecas = 5;
int quantNiveis = 3;
int quantPerguntas = 5;

int nivel;

char* perguntas[quantPecas][quantNiveis][quantPerguntas] =

                              {{{"fRAM1", "fRAM2", "fRAM3", "fRAM4", "fRAM5"}, //Perguntas da RAM (A0)
                                {"mRAM1", "mRAM2", "mRAM3", "mRAm4", "mRAM5"},
                                {"dRAM1", "dRAM2", "dRAM3", "dRAM4", "dRAM5"}},

                                {{"fCPU1", "fCPU2", "fCPU3", "fCPU4", "fCPU5"}, //Perguntas CPU (A1)
                                {"mCPU1", "mCPU2", "mCPU3", "mCPU4", "mCPU5"}, 
                                {"dCPU1", "dCPU2", "dCPU3", "dCPU4", "dCPU5"}},
                                
                                {{"fSSD1", "fSSD2", "fSSD3", "fSSD4", "fSSD5"}, //Perguntas da SSD (A3)
                                  {"mSSD1", "mSSD2", "mSSD3", "mSSD4", "mSSD5"}, 
                                  {"dSSD1", "dSSD2", "dSSD3", "dSSD4", "dSSD5"}},
                                  
                                {{"fGPU1", "fGPU2", "fGPU3", "fGPU4", "fGPU5"}, //GPU (A3)
                                  {"mGPU1", "mGPU2", "mGPU3", "mGPU4", "mGPU5"}, 
                                  {"dGPU1", "dGPU2", "dGPU3", "dGPU4", "dGPU5"}},
                                  
                                {{"fFON1", "fFON2", "fFON3", "fFON4", "fFON5"}, //FONTE (A4)
                                  {"mFON1", "mFON2", "mFON3", "mFON4", "mFON5"}, 
                                  {"dFON1", "dFON2", "dFON3", "dFON4", "dFON5"}}};    
                                                 
// acaba aqui

int reedSwitches[3] = {5, 6, 7, 8, 9};

const int redLedPin = 10;
const int greenLedPin = 11;

int buzzerPin = 12;

int cont;
int contBreak;

void setup() {
  Serial.begin(9600);

  pinMode(btnF, INPUT_PULLUP);
  pinMode(btnM, INPUT_PULLUP);
  pinMode(btnD, INPUT_PULLUP);

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  lcd.begin(16, 2); // Define a quantidade de caracteres usados na tela
}

void loop() {
  lcd.clear(); // Limpa a tela no começo do loop
  cont = 0;

  lcd.setCursor(0, 0); // Define caractere inicial e linha do que vai ser escrito na tela
  lcd.print("Selecione a");
  lcd.setCursor(0, 1);
  lcd.print("dificuldade"); // Define caractere inicial e linha do que vai ser escrito na tela

  while (true) {
    if (digitalRead(btnF) == LOW) {
      dificuldade = 0; // Retornando dificuldade fácil
      
      // Feedback na serial do estado do botão
      Serial.print("Botão verde = ");
      Serial.print(digitalRead(btnF));
      break;
    } else if (digitalRead(btnM) == LOW) {
      dificuldade = 1; // Retornando dificuldade média

      // Feedback na serial do estado do botão
      Serial.print("Botão amarelo = ");
      Serial.print(digitalRead(btnM));
      break;
    } else if (digitalRead(btnD) == LOW) {
      dificuldade = 2; // Retornando dificuldade difícil

      // Feedback na serial do estado do botão
      Serial.print("Botão vermelho = ");
      Serial.print(digitalRead(btnD));
      break;
    }
  }

  lcd.clear(); // Limpa a tela para rodas as perguntas

  for (int pergunta = 0; pergunta < 5; pergunta++) {
    // A depender da dificuldade a pergunta será passada direita para a esquerda na tela LCD
    if (dificuldade == 0) {
      lcd.setCursor(0, 0); // Define caractere inicial e linha do que vai ser escrito na tela
      lcd.print(perguntasF[pergunta]); // Pergunta a ser escrita
      delay(500);

      for (int posicao = 0; posicao < 40; posicao++) {
        lcd.scrollDisplayLeft(); 
        delay(300);
      }
    } else if (dificuldade == 1) {
      lcd.setCursor(0, 0); // Define caractere inicial e linha do que vai ser escrito na tela
      lcd.print(perguntasM[pergunta]); // Pergunta a ser escrita
      delay(500);

      for (int posicao = 0; posicao < 40; posicao++) {
        lcd.scrollDisplayLeft();
        delay(300);
      }
    } else if (dificuldade == 2) {
      lcd.setCursor(0, 0); // Define caractere inicial e linha do que vai ser escrito na tela
      lcd.print(perguntasD[pergunta]); // Pergunta a ser escrita
      delay(500);

      for (int posicao = 0; posicao < 40; posicao++) {
        lcd.scrollDisplayLeft();
        delay(300);
      }
    }

    contBreak = 0;

    // Feedback na serial da intensidade da luz sendo lida
    Serial.println("");
    Serial.print("Luz RAM: ");
    Serial.print(analogRead(A0));
    Serial.println("");
    Serial.print("Luz CPU: ");
    Serial.print(analogRead(A1));
    Serial.println("");
    Serial.print("Luz SSD: ");
    Serial.print(analogRead(A2));
    Serial.println("");
    Serial.print("Luz GPU: ");
    Serial.print(analogRead(A3));
    Serial.println("");
    Serial.print("Luz Fonte: ");
    Serial.print(analogRead(A4));

    while (true) {
      for (int i = cont; i < 5; i++) {
        if (i == pergunta) {
          if (analogRead(luz[pergunta]) < intensidadeLuzEncaixe) {
            digitalWrite(ledVerde, HIGH);
            delay(2000);
            digitalWrite(ledVerde, LOW);
            contBreak += 1;
            cont += 1;
            break;
          }
        } else if (analogRead(luz[i]) < intensidadeLuzEncaixe) {
          digitalWrite(ledVermelho, HIGH);
          delay(1000);
          digitalWrite(ledVermelho, LOW);
        }
      }

      if (contBreak != 0) {
        break;
      }
    }
  }
}