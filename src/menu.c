#include "menu.h"
#include "leitura.h"
#include "algorithms.h"

void menu() {
    int op = -1;
    char *text = NULL;

    #ifdef DEBUG
        printf ("\nDebug mode");
    #else
        printf("\nNormal Mode");
    #endif
    
    while(op != 0) {
        printf("\n\n   -- Menu --       \n");
        printf("1. Abrir arquivo        \n");
        printf("2. Boyer Moore          \n");
        printf("3. Shift-And exato      \n");
        printf("4. Shift-And aproximado \n");
        printf("0. Sair                 \n");
        printf("Opcao Escolhida: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                text = open_file();
                break;
            case 2:
                if(text == NULL) {
                    printf("\nLeia um arquivo primeiro.");
                    break;
                }
                execute_boyer_moore(text);
                break;
            case 3:
                if(text == NULL) {
                    printf("\nLeia um arquivo primeiro.");
                    break;
                }
                execute_shift_and_exato(text);
                break;
            case 4:
                if(text == NULL) {
                    printf("\nLeia um arquivo primeiro.");
                    break;
                }
                execute_shift_and_aprox(text);
                break;
            case 0:
                stop();
                break;
            default:
                invalid();
                break;
        }
    }

}

char* open_file() {
    char *text;
    char name[50];

    printf("Nome do arquivo (sem extensao): ");
    scanf(" %[^\n]s", name);

    if(read_file(&text, name) == 0) printf("\nArquivo vazio");
    else                            printf("\nSucesso!");

    return text;
}

void execute_boyer_moore(char *text) {
    int indice;
    char *pattern;
    pattern = (char*) malloc(100*sizeof(char));
    
    printf("Qual o padrao procurado? ");
    scanf(" %[^\n]s", pattern);

    indice = boyer_moore(text, pattern);
    if(indice == -2) {
        printf("\nPadrao nao encontrado.");
    } else {
        printf("\nBoyer Moore: Match no indice: %d", indice);
    }
    free(pattern);
}

void execute_shift_and_exato(char *text) {
    int indice;
    char *pattern;
    pattern = (char*) malloc(100*sizeof(char));

    printf("Qual o padrao procurado? ");
    scanf(" %[^\n]s", pattern);

    indice = shift_and_exact(text, pattern);
    if(indice == -2) {
        printf("\nPadrao nao encontrado.");
    } else {
        printf("\nBoyer Moore: Match no indice: %d", indice);
    }

    free(pattern);
}

void execute_shift_and_aprox(char *text) {
    int alg, k, ins, rem, subs;
    char *pattern;
    pattern = (char*) malloc(100*sizeof(char));

    printf("Qual o padrao procurado? ");
    scanf(" %[^\n]s", pattern);

    printf("Distancia de Edicao: ");
    scanf("%d", &k);
    printf("Permitir insercao? (1->Sim | 0->Nao)");
    scanf("%d", &ins);
    printf("Permitir remocao? (1->Sim | 0->Nao)");
    scanf("%d", &rem);
    printf("Permitir substituicao? (1->Sim | 0->Nao)");
    scanf("%d", &subs);
    shift_and_aprox(text, pattern, k, ins, rem, subs);

    free(pattern);
}

void stop() {
    printf("\nSair!\n\n");
}

void invalid() {
    printf("Opcao Invalida!\n");
}