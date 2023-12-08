#include <stdlib.h>


#include "getFromDictionary.h"

#define STARTPOSITION 12 // the begining of entry data part


entryData* getEntry(FILE* dictionary, int offset, int childCount){
    fseek(dictionary, offset, SEEK_SET);//move pointer to required part of dictionary
    entryData* result = (entryData*)calloc(0, sizeof(entryData));
    unsigned char formatFlags;
    for(int i = 0; i < childCount; i++){
        result = (entryData*)realloc(result, sizeof(entryData)*(i+1));
        formatFlags = getc(dictionary);
        result[i].format = formatFlags >> 4;
        result[i].flags = formatFlags & 0x0F;
        fread_s(&(result[i].sequence), sizeof(unsigned short), 2, 1, dictionary);
        if(result[i].sequence != i){
            return NULL;
        }
        fread_s(&result[i].childPointerOffset, sizeof(unsigned short), 2, 1, dictionary);
        fread_s(&result[i].childCount, sizeof(unsigned short), 2, 1, dictionary);
        result[i].nameLength = getc(dictionary);
        fread_s(&result[i].nameOffset, sizeof(unsigned short), 2, 1, dictionary);
    }
    return result;
}


char* getName(unsigned short sequence, entryData* entry, FILE* dicionary){
    int length = entry[sequence].nameLength;
    char* result = (char*)calloc(1, length); 
    unsigned short offset = entry[sequence].nameOffset;
    fseek(dicionary, offset, SEEK_SET);
    fread_s(result, length, length, 1, dicionary);
    return result;
}