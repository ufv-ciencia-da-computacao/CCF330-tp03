#include "algorithms.h"
#include <math.h>

#define ASCII_CHAR 256

int max(int a, int b) {
    return a > b ? a : b;
}

int shift_and_exact(char* text, char* pattern) {
    int m = strlen(pattern);
    unsigned long R;
    unsigned long pattern_mask[ASCII_CHAR];
    
    if (pattern[0] =='\0') return 1;
    if (m > 31) return -2; // wordsize

    R = 0;

    for (int i = 0; i < ASCII_CHAR; i++) pattern_mask[i] = 0;
    for (int i = 0; i < m; i++) pattern_mask[pattern[i]] = pattern_mask[pattern[i]] + pow(2, i);

    for (int i = 0; i < text[i] != '\0'; i++) {
        R = ((R << 1) + 1) & pattern_mask[text[i]];
        if (R & (unsigned long) pow(2, (m-1))) return i-m+1; 
    }
    
    return -2;
}

void occurrence_shift(char* str, int size, int badchar[ASCII_CHAR]) {
    for (int i = 0; i < ASCII_CHAR; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++) {
        badchar[(int) str[i]] = i;
    }    
}

int boyer_moore(char* text, char* pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[ASCII_CHAR];

    occurrence_shift(pattern, m, badchar);

    int shift = 0;

    while (shift <= (n-m)) {
        int j = m-1;

        while (j >= 0 && pattern[j] == text[shift+j]) j--;

        if (j < 0) {
            return shift; // Tem como fazer a tarefa D1 aqui

            shift += (shift+m < n) ? m-badchar[text[shift+m]] : 1;
        } else {
            shift += max(1, j - badchar[text[shift+j]]);
        }        
    }
}