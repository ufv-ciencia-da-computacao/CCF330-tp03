#define __ALGORITHMS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shift_and_exact(char* text, char* pattern);
int boyer_moore(char* text, char* pattern);

/*
 * Input Parameters
 * text
 * pattern - pattern to be found in text
 * K - edition distace (exact match : 0);
 * insert - permit to insert (yes : 1, no : 0); 
 * remove - permit to remove (yes : 1, no : 0);
 * alter - permit to alter (yes : 1, no : 0)
*/
void shift_and_aprox(char* text, char* pattern, long k, int insert, int remove, int alter);