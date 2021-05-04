#include "algorithms.h"

int main () {
    char text[] = "Projeto e Análise de Algoritmos";
    char pattern[] = "Algorimos";

    int index = boyer_moore(text, pattern);
    printf("Boyer Moore: Match no índice: %d\n", index+1);

    index = shift_and_exact(text, pattern);
    printf("Shift-And: Match no índice: %d\n", index+1);
    
    return 0;
}