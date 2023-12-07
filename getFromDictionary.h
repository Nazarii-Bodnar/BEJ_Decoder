#include <stdio.h>
#include <stdlib.h>

#include "definedTypes.h"

entryData* getEntry(FILE* dictionary, int offset, int childCount);
char* getName(unsigned short sequence, entryData* entry, FILE* dicionary);