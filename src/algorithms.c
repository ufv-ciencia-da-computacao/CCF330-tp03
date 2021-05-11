#include "algorithms.h"
#include <math.h>

#define ASCII_CHAR 256

int max(int a, int b) {
    return a > b ? a : b;
}

void shift_and_exact(char* text, char* pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    unsigned long R;
    unsigned long pattern_mask[ASCII_CHAR];

    R = 0;

    for (int i = 0; i < ASCII_CHAR; i++) pattern_mask[i] = 0;
    for (int i = 1; i <= m; i++)         pattern_mask[pattern[i-1]+127] |= 1 << (m-i);

    for (int i = 0; i < n; i++) {
        R = ((((unsigned long)R) >> 1) | 
          (1 << (m - 1))) & pattern_mask[text[i] + 127];
        if ((R & 1) != 0) printf("Shift-And Exato: Match no indice: %d\n", i-m+2);
    }
    
    return;
}

void occurrence_shift(char* str, int size, int badchar[ASCII_CHAR]) {
    for (int i = 0; i < ASCII_CHAR; i++)
        badchar[i] = -1;

    for (int i = 0; i < size; i++) {
        badchar[(int) str[i]] = i;
    }    
}

void boyer_moore(char* text, char* pattern) {
    int m = strlen(pattern);
    int n = strlen(text);

    int badchar[ASCII_CHAR];

    occurrence_shift(pattern, m, badchar);

    int shift = 0;
    int flag = 0;

    while (shift <= (n-m)) {
        int j = m-1;

        while (j >= 0 && pattern[j] == text[shift+j]) j--;

        if (j < 0) {
            printf("\nBoyer-Moore: Match no indice: %d", shift+1);
            flag=1;
            shift += (shift+m < n) ? m-badchar[text[shift+m]] : 1;
        } else {
            shift += max(1, j - badchar[text[shift+j]]);
        }        
    }

    if (flag==0) printf("Padrão não encontrado!\n");
    return;
}

void shift_and_aprox(char* text, char* pattern, long k, int insert, int remove, int alter) {
    long i, j, Ri, Rant, Rnovo, count = 0, flag = 1;
    long R[ASCII_CHAR + 1], mask[ASCII_CHAR];
    long m = strlen(pattern);
    long n = strlen(text);

    if (pattern[0] == '\0') return;

    /*-- Pre Processing --*/
    for(i=0; i<ASCII_CHAR; i++) mask[i] = 0;
    for(i=1; i<=m; i++)         mask[pattern[i-1] + 127] |= 1 << (m-i);
    
    /*-- Research --*/
    R[0] = 0;
    Ri = 1 << (m-1);
    for(i=1; i<=k; i++) R[i] = (1<<(m-i)) | R[i-1];

    if(insert && remove && alter) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | (unsigned long)(Rnovo >> 1) /*Remove*/
                        | Rant /*Insert*/
                        | (unsigned long)(Rant >> 1) /*Substitution*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else if(insert && remove) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | (unsigned long)(Rnovo >> 1) /*Remove*/
                        | Rant /*Insert*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else if(insert && alter) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | Rant /*Insert*/
                        | (unsigned long)(Rant >> 1) /*Substitution*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else if(remove && alter) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | (unsigned long)(Rnovo >> 1) /*Remove*/
                        | (unsigned long)(Rant >> 1) /*Substitution*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else if(insert) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | Rant /*Insert*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else if(remove) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | (unsigned long)(Rnovo >> 1) /*Remove*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else if(alter) {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;
            for(j=1; j<=k; j++) {
                Rnovo = ((((unsigned long)R[j]) >> 1) & mask[text[i] + 127])
                        | (unsigned long)(Rant >> 1) /*Substitution*/;
                Rant = R[j];
                R[j] = Rnovo | Ri;
            }
            
            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
    } else {
        for(i=0; i<n; i++) {
            Rant = R[0];
            Rnovo = ((((unsigned long)Rant) >> 1) | Ri) & mask[text[i]+127];
            R[0] = Rnovo;

            if((Rnovo & 1) != 0) {
                printf("\nShift-And Aprox: Match no indice: %ld", i+1);
                flag = 0;
            }
        }
        
        
    }


    if(flag) printf("\nNenhum match aproximado!");

}