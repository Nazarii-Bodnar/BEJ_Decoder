#include <stdlib.h>
#include "BEJDecoder.h"


int unintHandler(int start, char length, char* data){
    int result = 0;
    for(int i = 0; i < length; i++){
        result += data[start+i];
    }
    return result;
}

void copyArray(char* source, char* dest, int length, int start){
    for(int i = 0; i < length; i++){
        dest[i] = source[start+i];
    }
}

bejTuple* separateInTuples(char* source, int sourceLength, int startPoint){
    bejTuple *result = (bejTuple*)calloc(0, sizeof(bejTuple));
    int i = startPoint;
    int count = 0;
    while(i <= sourceLength){//every iteration is one tuple
        result = (bejTuple*)realloc(result, count*sizeof(bejTuple));
        result[count].sequence = source[i+1];
        i += source[i]+1;//set iterator to next tuple member
        result[count].format = source[i];
        i++;
        result[count].length = unintHandler(i+1, source[i], source);
        i += source[i]+1;
        result[count].value = (char*)calloc(result[count].length, sizeof(char));
        copyArray(source, result[count].value, result[count].length, i);
        i += result[count].length+1;

        if(((result[count].format >> 4) == 0) || ((result[count].format >> 4) == 1)){
            result[count].children = separateInTuples(result[count].value, result[count].length, i);
        }
        else{
            result[count].children = NULL;
        }

        count++;
    };

    return result;
}

