#include <stdio.h>
#include <stdlib.h>

#include "writeJSON.h"

unsigned int decodeUnnInt(unsigned int unnIntLength, int *index, unsigned char* source){
    if(unnIntLength == 0){
        return 0;
    }

    unsigned int result = 0;
    for(int i = 0; i < unnIntLength; i++){
        result |= source[(*index)] << i*8;
        (*index)++;
    }
    return result;
}

unsigned int getRealValue(int* index, unsigned char* source){
    int length = source[*index];
    (*index)++;
    unsigned int result = decodeUnnInt(length, index, source);
    return result;
}


void writeParametr(FILE *output, char *parametr){
    fprintf_s(output, "\"%s\": ", (char*)parametr);
    free(parametr);
}


void writeString(FILE* output, void* data){
    fprintf_s(output, "\"%s\"", (char*)data);
}


void writeNumber(FILE* output, unsigned char* data, unsigned int length){
    int index = 0;
    fprintf_s(output, "%u", decodeUnnInt(length, &index, data));
}

void writeBoolean(FILE* output, void* data){
    int value = (int)*((char*)data);
    if(value){
        fprintf_s(output, "%s", "true");
    }
    else{
        fprintf_s(output, "%s", "false");
    }

}


void writeReal(FILE* output, void* data){
    unsigned char* source = (unsigned char*)data;
    int length;
    int index = 0;

    unsigned int wholeLength = getRealValue(&index, source);
    unsigned int whole = decodeUnnInt(wholeLength, &index, source);
    unsigned int zeroCount = getRealValue(&index, source);
    unsigned int fraq = getRealValue(&index, source);
    unsigned int lenghtExp = getRealValue(&index, source);
    unsigned int exp = decodeUnnInt(lenghtExp, &index, source);

    char* zeros = (char*)calloc(zeroCount+1, sizeof(char));
    for(int i = 0; i < zeroCount; i++){
        zeros[i] = '0';
    }
    zeros[zeroCount] = '\0';
    char sign;
    if(exp >= 0){
        sign = '+'; 
    }
    else{
        sign = '-';
    }
    fprintf_s(output, "%d.%s%de%c%d", whole, zeros, fraq, sign, exp);
    free(zeros);
}

void writeNull(FILE* output){
    fprintf_s(output, "null");
}