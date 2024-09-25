 // Biblioteca da tela LCD
#include <stdlib.h>
#include <iostream>
#include <ctime>

int main () {

    int teste;

    int quantPecas = 5;
    int quantNiveis = 3;
    int quantPerguntas = 5;

    int nivel;

    srand(time(NULL));

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
    
    int i = 0;

    std::cout << "Fácil, médio ou difícil? (0 = F, 1 = M, 2 = D)\n";
    std::cin >> nivel;

    int ordemPerguntas[quantPerguntas] = {0, 0, 0, 0, 0}; // lista que vai definir ordem que cada pergunta da dificuldade escolhida de cada peça irá aparecer, retorna lista de 0-4 embaralhada.
    int ordemPecas[quantPecas] = {0, 0, 0, 0, 0}; // lista que vai definir ordem que cada peca irá aparecer, retorna lista de 0-4 embaralhada.

    for (int i = 0; i < quantPecas; i++){ // PARA PECA INDIVIDUAL

      int countPecas = 0;

      while(countPecas < quantPecas){ // o countpecas serve para verificar se a lista aleatoria das pecas já está completa.

          bool possivelPecas = true;
          int numeroAleatorioPecas = rand() % quantPecas; // gera numero aleatorio

          for (int x = 0; x < countPecas; x++){
              if (ordemPecas[x] == numeroAleatorioPecas){ // verifica se está na lista, se nao estiver loop continua
                  possivelPecas = false;
                  break;
              }
          }

          if (possivelPecas){
              ordemPecas[countPecas] = numeroAleatorioPecas; // caso nao estiver, adiciona.
              countPecas++; // se o count chegar a 5 (todos elementos serem preenchidos na lista, programa para)
            }
        }
    }

    for (int j = 0; j < quantPerguntas; j++){

        int countPerguntas = 0;

        while(countPerguntas < quantPerguntas){ // o countPerguntas serve para verificar se a lista aleatoria das perguntascjá está completa.

            bool possivelPerguntas = true;
            int numeroAleatorioPerguntas = rand() % quantPerguntas; // gera numero aleatorio

            for (int y = 0; y < countPerguntas; y++){
                if (ordemPerguntas[y] == numeroAleatorioPerguntas){ // verifica se está na lista, se nao estiver loop continua
                    possivelPerguntas = false;
                    break;
                }
            }

            if (possivelPerguntas){
                ordemPerguntas[countPerguntas] = numeroAleatorioPerguntas; // caso nao estiver, adiciona.
                countPerguntas++; // se o count chegar a 5 (todos elementos serem preenchidos na lista, programa para)
                }
            }
    }



    for (int y = 0; y < quantPecas; y++){
        std::cout<< perguntas[ordemPecas[y]][nivel][ordemPerguntas[y]] << "\n";
    }

    return 0;
}
