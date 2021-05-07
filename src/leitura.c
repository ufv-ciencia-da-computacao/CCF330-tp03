#include <string.h>
#include "leitura.h"

int read_file(char **text, char *fileName) {
    FILE *file;
    char path[100];
    int i=0;
    size_t pos, length;

    strcpy(path, "./data/");
    strcat(path, fileName);
    strcat(path, ".txt");

    file = fopen(path, "r");

    if (file == NULL) {
        perror("\nArquivo nao pode ser lido!");
        fclose(file);
        return 0;
    }
    
    pos = ftell(file);           // Current position
    fseek(file, 0, SEEK_END);    // Go to end
    length = ftell(file) + 1;    // read the position which is the size
    fseek(file, pos, SEEK_SET);  // restore original position

    (*text) = (char*) malloc(length*sizeof(char));    
    while (!feof(file)) {
        fscanf(file, "%c", &(*text)[i]);
        ++i;
    }
    (*text)[length-1] = '\0';
    
    fclose(file);
    return 1;
}