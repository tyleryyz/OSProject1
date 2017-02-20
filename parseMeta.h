#ifndef PARSEMETA_H
#define PARSEMETA_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

struct Points *parseMeta(char *file_input[], int* count);
void RemoveSpaces(char* string);


struct Points
  {
    char file_letter;
    char *operation;
    int cycle_time;
  };

#endif
