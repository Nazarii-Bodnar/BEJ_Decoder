#include <stdlib.h>

typedef struct {
    unsigned int sequence;
    unsigned char format;
    unsigned int length;
    char *value;
    void *children;
} bejTuple;


int unintHandler(int start, char length, char* data);
void copyArray(char* source, char* dest, int length, int start);
bejTuple* separateInTuples(char* source, int sourceLength, int startPoint);