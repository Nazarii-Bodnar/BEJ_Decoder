#include <stdlib.h>
#include <stdio.h>

#include "BEJDecoder.h"

//TODO: unIntHandler not writing variables
void unIntHandler(FILE* source, unsigned int* output){
    unsigned char length = fgetc(source);
    int check;
    check = fread_s(output, sizeof(unsigned int), length, 1, source);
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
            result[index].children = separateInTuples(source, 0, childCount);
        }
        else{
            result[index].children = NULL;
            result[index].value = calloc(result[index].length, sizeof(char));
            fread_s(result[index].value, result[index].length, result[index].length, 1, source);
        }
        index++;
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


