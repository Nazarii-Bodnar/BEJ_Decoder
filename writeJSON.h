#include <stdio.h>
#include "definedTypes.h"

void writeParametr(FILE* output, char* parametr);
void writeSet(FILE* output, bejTuple* data);
void writeArray(FILE* output, bejTuple* data);
void writeString(FILE* output, char* data);
void writeNumber(FILE* output, char* data);