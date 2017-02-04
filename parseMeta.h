#ifndef PARSEMETA_H
#define PARSEMETA_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Points *parseMeta(char *file_input[]);

struct Points
  {
    char comp_letter[2];
    char operation[16];
    int cycle_time;
  };

#endif
