#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "slist.h"
#include "file.h"

void compress(FILE * input, FILE * output, char * inputname);
void decompress(FILE * input);

int decode(List * list, int code, FILE * output);