#include <iostream>

int main () {

    srand(time(NULL)); 

    int numeros[5] = {0, 0, 0, 0, 0}; 
    std::string perguntas[5] = {"a", "b", "skibidi", "toilet", "c"};
    int count = 0;

    while(count < 5){
        bool possivel = true;
        int numeroAleatorio = rand() % 5;

        for (int i = 0; i < count; i++){
            if (numeros[i] == numeroAleatorio){
                possivel = false;
                break;
            }
        }

        if (possivel){
            numeros[count] = numeroAleatorio;
            count++;
        }
    }

    for (int i = 0; i < 5; i++){
        std::cout << perguntas[numeros[i]] << std::endl;
    }

    return 0;
}
