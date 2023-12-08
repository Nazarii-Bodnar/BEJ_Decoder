#include <stdlib.h>
#include <stdio.h>

#include "BEJDecoder.h"


void unIntHandler(FILE* source, unsigned int* output){
    unsigned char length = fgetc(source);
    int check;
    check = fread_s(output, sizeof(unsigned int), length, 1, source);
}

bejTuple* separateInTuples(FILE* source, int startPoint, unsigned int maxCount){
    bejTuple *result = (bejTuple*)calloc(0, sizeof(bejTuple));
    if(startPoint){
        fseek(source, startPoint, SEEK_SET);
    }
    int index = 0;
    unsigned int childCount = 0;
    while(!feof(source) && maxCount && index < maxCount){
        result = (bejTuple*)realloc(result, (index+1)*sizeof(bejTuple));
        result[index].sequence = 0;
        unIntHandler(source, &result[index].sequence);
        unsigned char formatFlags = fgetc(source);
        result[index].format = formatFlags >> 4;
        result[index].flags = formatFlags & 0x0F;
        result[index].length = 0;
        unIntHandler(source, &result[index].length);
        if(result[index].format == 0x00 || result[index].format == 0x01){
            unIntHandler(source, &childCount);
            result[index].childCount = childCount;
            result[index].children = separateInTuples(source, 0, childCount);
        }
        else{
            result[index].children = NULL;
            result[index].childCount = 0;
            result[index].value = calloc(result[index].length, sizeof(char));
            fread_s(result[index].value, result[index].length, result[index].length, 1, source);
        }
        index++;
    }

    return result;
}


