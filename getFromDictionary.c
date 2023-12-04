#include "stdio.h"

#define STARTPOSITION 12 // the begining of entry data part


int getNamePosition(unsigned int format, unsigned int sequence, int entryCount, FILE* dictionary){
    char dictionaryFormat;
    int dictionarySequence;
    int result;
    dictionary += (STARTPOSITION+sequence);
    for(int i = sequence; i < entryCount; i++){
        dictionary += 10;
        dictionaryFormat = fgetc(dictionary) >> 4;
        fread_s(&dictionarySequence, sizeof(int), sizeof(int), 1, dictionary+1);
        if(sequence == dictionarySequence && format == dictionaryFormat){
            fread_s(&result, sizeof(int), sizeof(int), 1, dictionary+7);
            break;
        }
    }
    return result;
}

char* getName(FILE* dictionary){
    
}