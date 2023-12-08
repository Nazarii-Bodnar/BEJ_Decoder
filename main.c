#include "BEJDecoder.h"
#include "getFromDictionary.h"
#include "writeJSON.h"
#include "stdio.h"

void decode(FILE* input, FILE* dictionary, FILE* output, int startPoint, int maxCount, int entryOffset, int setName){
    bejTuple* tuples = separateInTuples(input, startPoint, maxCount);
    entryData* entry = getEntry(dictionary, entryOffset, maxCount);
    for(int i = 0; i < maxCount; i++){
        switch(tuples[i].format){
            case 0x00:
                if(setName){
                    writeParametr(output, getName(tuples[i].sequence, entry, dictionary));
                }
                decode(input, dictionary, output, 0, tuples[i].childCount, entry[tuples[i].sequence].childPointerOffset, 1);
                break;
        }
    }
}


int main(){
    FILE* input;
    FILE* dictionary;
    FILE* output;
    fopen_s(&input, "example.bin", "rb");
    fopen_s(&output, "example.json", "w");
    fopen_s(&dictionary, "C:/Users/Nazar/Documents/BEJ/DSP8010_2023_1/dictionaries/Memory_v1.bin", "rb");

    bejTuple* tuples = separateInTuples(input, 7, 1);
    entryData* entry = getEntry(dictionary, 12, 1);

}