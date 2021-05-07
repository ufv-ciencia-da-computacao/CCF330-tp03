#ifndef MENU_H
#define MENU_H

#include <stdio.h>

void menu();

char* open_file();

void execute_boyer_moore(char *text);

void execute_shift_and_exato(char *text);

void execute_shift_and_aprox(char *text);

void stop();

void invalid();

#endif