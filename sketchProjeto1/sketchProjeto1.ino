#include <LiquidCrystal.h> // Biblioteca da tela LCD

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int btnF = 10; // Botão verde
const int btnM = 7; // Botão amarelo
const int btnD = 6; // Botão vermelho

int dificuldade;

char* perguntasF[5] = {"Qual peca armazena dados temporariamente", "Qual e o cerebro do computador..........", "Qual peca armazena dados permanentemente", "Qual peca processa graficos e imagens...", "Qual peca fornece energia ao computador."}; // Perguntas fáceis
char* perguntasM[5] = {"Qual peca tem frequencias e latencias...", "Qual executa varias tarefas simultaneas..", "Qual peca usa memoria flash.............", "Qual peca acelera a criacao de imagens..", "Qual peca converte energia eletrica....."}; // Perguntas médias
char* perguntasD[5] = {"Qual peca pode ser DDR3, DDR4 ou DDR5...", "Qual peca usa arquiteturas x86 ou ARM...", "Qual peca usa SATA, NVMe ou PCIe........", "Qual peca suporta Ray Tracing e DLSS....", "Qual tem certificacoes de eficiencia...."}; // Perguntas difíceis

int luz[5] = { A0, A1, A2, A3, A4 }; // A0 - RAM, A1 - CPU, A2 - SSD, A3 - GPU, A4 - Fonte
const int intensidadeLuzEncaixe = 30;

const int ledVermelho = 8;
const int ledVerde = 9;
int cont; // Contador para checagem dos encaixes
int contBreak; // Contador para dar break em um while (true)

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
