#include <stdlib.h>
#include <stdio.h>

#include "BEJDecoder.h"

//TODO: unIntHandler not writing variables
void unIntHandler(FILE* source, unsigned int* output){
    unsigned char length = fgetc(source);
    fread_s(output, sizeof(unsigned int), length, 1, source);
}

void copyArray(char* source, char* dest, int length, int start){
    for(int i = 0; i < length; i++){
        dest[i] = source[start+i];
    }
}

bejTuple* separateInTuples(FILE* source, int startPoint, unsigned int maxCount){
    bejTuple *result = (bejTuple*)calloc(0, sizeof(bejTuple));
    if(startPoint){
        fseek(source, startPoint, SEEK_SET);
    }
    int count = 1;
    unsigned int childCount = 0;
    while(!feof(source) && maxCount && count <= maxCount){
        result = (bejTuple*)realloc(result, count*sizeof(bejTuple));
        result[count].sequence = 0;
        unIntHandler(source, &result[count].sequence);
        unsigned char formatFlags = fgetc(source);
        result[count].format = formatFlags >> 4;
        result[count].flags = formatFlags & 0x0F;//TODO: flag is to big
        result[count].length = 0;
        unIntHandler(source, &result[count].length);
        if(result[count].format == 0x00 || result[count].format == 0x01){
            unIntHandler(source, &childCount);
            result[count].children = separateInTuples(source, 0, childCount);
        }
        else{
            result[count].children = NULL;
            result[count].value = calloc(result[count].length, sizeof(char));
            fread_s(result[count].value, result[count].length, result[count].length, 1, source);
        }
        count++;
    }

    return result;
}

// bejTuple* separateInTuples(char* source, int sourceLength, int startPoint){
//     bejTuple *result = (bejTuple*)calloc(0, sizeof(bejTuple));
//     int i = startPoint;
//     int count = 0;
//     while(i <= sourceLength){//every iteration is one tuple
//         result = (bejTuple*)realloc(result, count*sizeof(bejTuple));
//         result[count].sequence = source[i+1];
//         i += source[i]+1;//set iterator to next tuple member
//         result[count].format = source[i];
//         i++;
//         result[count].length = unintHandler(i+1, source[i], source);
//         i += source[i]+1;
//         result[count].value = (char*)calloc(result[count].length, sizeof(char));
//         copyArray(source, result[count].value, result[count].length, i);
//         i += result[count].length+1;

//         if(((result[count].format >> 4) == 0) || ((result[count].format >> 4) == 1)){
//             result[count].children = separateInTuples(result[count].value, result[count].length, i);
//         }
//         else{
//             result[count].children = NULL;
//         }

//         count++;
//     };

//     return result;
// }


