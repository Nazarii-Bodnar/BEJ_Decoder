#include <stdlib.h>
#include <stdio.h>
#include "definedTypes.h"



void unIntHandler(FILE* source, unsigned int* output);
void copyArray(char* source, char* dest, int length, int start);
void getSetAndArray(FILE* source, void* output, unsigned int* count, unsigned int* outputLength, unsigned int* offset);
bejTuple* separateInTuples(FILE* source, int startPoint, unsigned int maxCount);