#include <string.h>
#include "leitura.h"

int read_file(char **text, char *fileName) {
    FILE *file;
    char path[2000];
    int i=0;
    size_t pos, length;

    // strcpy(path, "./data/");
    strcpy(path, fileName);
    // strcat(path, ".txt");

    file = fopen(path, "r");

    if (file == NULL) {
        perror("\nArquivo nao pode ser lido!");
        fclose(file);
        return 0;
    }
    
    pos = ftell(file);           // Current position
    fseek(file, 0, SEEK_END);    // Go to end
    length = ftell(file) + 1;    // read the position which is the size
    fseek(file, 0, SEEK_SET);    // restore original position

    
    (*text) = (char*) malloc(length*sizeof(char)); 
    size_t read_size = fread((*text), sizeof(char), length, file);  
    printf("%ld\n%ld\n", read_size, length);
    (*text)[length] = '\0';
    
    fclose(file);
    return 1;
}