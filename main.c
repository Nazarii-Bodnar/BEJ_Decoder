#include "BEJDecoder.h"
#include "getFromDictionary.h"
#include "stdio.h"


int main(){
    FILE* file;
    fopen_s(&file, "C:/Users/Nazar/Documents/BEJ/RDE-Dictionary/example.bin", "rb");
    bejTuple* res = separateInTuples(file, 7, 1);
    fclose(file);
    free(res);
    return 1;
}