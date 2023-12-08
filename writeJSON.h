#include <stdio.h>
#include "definedTypes.h"

unsigned int decodeUnnInt(int unnIntLength, int* index, unsigned char* source);
unsigned int getRealValue(int* index, unsigned char* source);

void writeParametr(FILE* output, char* parametr);
void writeString(FILE* output, void* data);
void writeNumber(FILE* output, unsigned int data);
void writeBoolean(FILE* output, void* data);
void writeReal(FILE* output, void* data);