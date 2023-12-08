#include <stdio.h>
#include "definedTypes.h"

unsigned int decodeUnnInt(unsigned int unnIntLength, int* index, unsigned char* source);
unsigned int getRealValue(int* index, unsigned char* source);

void writeParametr(FILE* output, char* parametr);
void writeString(FILE* output, void* data);
void writeNumber(FILE* output, unsigned char* data, unsigned int length);
void writeBoolean(FILE* output, void* data);
void writeReal(FILE* output, void* data);
void writeNull(FILE* output);