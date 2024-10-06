#include <iostream>

// Button pins for difficulty selection

int difficulty;                    // Variable to store selected difficulty level

// Constants representing the number of blocks, levels, and questions
const int blocks = 5;
const int levels = 3;
const int questions = 5;

// Array storing the question strings for each block and difficulty level
char* perguntas[blocks][levels][questions] =

                                  {{{"ePowerSupply1", "ePowerSupply2", "ePowerSupply3", "ePowerSupply4", "ePowerSupply5"},    // Easy Power supply questions
                                    {"nPowerSupply1", "nPowerSupply2", "nPowerSupply3", "nPowerSupply4", "nPowerSupply5"},    // Normal Power supply questions
                                    {"hPowerSupply1", "hPowerSupply2", "hPowerSupply3", "hPowerSupply4", "hPowerSupply5"}},   // Hard Power supply questions

                                   {{"eCpu1", "eCpu2", "eCpu3", "eCpu4", "eCpu5"},    // Easy CPU questions
                                    {"nCpu1", "nCpu2", "nCpu3", "nCpu4", "nCpu5"},    // Normal CPU questions
                                    {"hCpu1", "hCpu2", "hCpu3", "hCpu4", "hCpu5"}},   // Hard CPU questions
                                    
                                    {{"eRam1", "eRam2", "eRam3", "eRam4", "eRam5"},   // Easy RAM questions
                                     {"nRam1", "nRam2", "nRam3", "nRam4", "nRam5"},   // Normal RAM questions
                                     {"hRam1", "hRam2", "hRam3", "hRam4", "hRam5"}},  // Hard RAM questions
                                     
                                    {{"eSsd1", "eSsd2", "eSsd3", "eSsd4", "eSsd5"},   // Easy SSD questions
                                     {"nSsd1", "nSsd2", "nSsd3", "nSsd4", "nSsd5"},   // Normal SSD questions
                                     {"hSsd1", "hSsd2", "hSsd3", "hSsd4", "hSsd5"}},  // Hard SSD questions
                                     
                                    {{"eGpu1", "eGpu2", "eGpu3", "eGpu4", "eGpu5"}, // Easy GPU questions
                                     {"nGpu1", "nGpu2", "nGpu3", "nGpu4", "nGpu5"}, // Normal GPU questions
                                     {"hGpu1", "hGpu2", "hGpu3", "hGpu4", "hGpu5"}}}; // Hard GPU questions

void randomBlocksOrder(int array[], int length);
void randomQuestions(int array[], int length);
int setDifficulty(int btn1, int btn2, int btn3);

void loop() {

  int cont = 0;               // Variable to track the current block

  // Display instructions for difficulty selection
  std::cout << "Selecione a dificuldade: " << std::endl;

  std::cin >> difficulty;

  // Call function to set difficulty based on button input

  // Arrays to store the random order of blocks and questions

  int questionsArray[questions];
  int blocksOrder[blocks];

  srand(time(NULL)); 

  randomBlocksOrder(blocksOrder, blocks); // Generate a random order for blocks
  randomQuestions(questionsArray, questions); // Generate a random order for questions

  // Loop through each block (5 blocks)
  for (int j = 0; j < 5; j++) {

    // Display the question for the selected difficulty and block
    std::cout << perguntas[blocksOrder[j]][difficulty][questionsArray[j]] << std::endl;

    int contBreak = 0;          // Variable to exit the inner loop

    // Wait for the correct reed switch input
    while (true) { // ?
      for (int k = cont; k < 5; k++) {
        int resposta;
        std::cout << "Resposta certa?" << std::endl;
        std::cin >> resposta;
        if (resposta == 1){
            std::cout << "Certo!" << std::endl;

            cont++;
            contBreak++;

            break;
        } else {
            std::cout << "Errado! Tende de novo" << std::endl;
        }
      }

      if (contBreak != 0) {
        break;  // Exit inner loop when correct switch is pressed
      }
    }
  }
}

// Function to set difficulty level based on button input
int setDifficulty(int btn1, int btn2, int btn3) {
    int escolha;
    std::cout << "Dificuldade 0, 1, 2?" << std::endl;
    std::cin >> escolha;
  while (true) {
    if (escolha == 0) {
    return 0;  // Easy difficulty
    } else if (escolha == 1) {
    return 1;  // Normal difficulty
    } else if (escolha == 2) {
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

