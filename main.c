#include "BEJDecoder.h"
#include "getFromDictionary.h"
#include "writeJSON.h"
#include "stdio.h"


void decode(FILE* input, FILE* dictionary, FILE* output, int startPointInput, int maxCountInput, int maxCountEntry, int entryOffset, int setName){
    bejTuple* tuples = separateInTuples(input, startPointInput, maxCountInput);
    entryData* entry = getEntry(dictionary, entryOffset, maxCountEntry);
    int sequence;
    int index = 0;
    for(int i = 0; i < maxCountInput; i++){
        if(setName){
            writeParametr(output, getName(tuples[i].sequence, entry, dictionary));
        }
        switch(tuples[i].format){
            case 0x00:
            case 0x01:
                // array have no name, array format is 1, so i simply invert it and pass as setName
                //TODO: replecate that scary if else to something mentally helthy
                if(tuples[i].format){
                    fprintf_s(output, "[\n");
                }
                else{
                    fprintf_s(output, "{\n");
                }
                decode(input, dictionary, output, tuples[i].valueOffset, tuples[i].childCount, entry[tuples[i].sequence].childCount, entry[tuples[i].sequence].childPointerOffset, !tuples[i].format);
                if(tuples[i].format){
                    fprintf_s(output, "]\n");
                }
                else{
                    fprintf_s(output, "}\n");
                }
                break;
            case 0x02:
                writeNull(output);
                break;
            case 0x03:
                writeNumber(output, tuples[i].value, tuples[i].length);
                break;
            case 0x04:
                entryData* childEntry = getEntry(dictionary, entry[tuples[i].sequence].childPointerOffset, entry[tuples[i].sequence].childCount);
                sequence = getRealValue(&index, tuples[i].value);
                switch(childEntry[sequence].format){
                    case 0x05:
                        writeString(output, getName(sequence, childEntry, dictionary));
                        break;
                    default:
                        fprintf(output, "\"enum eroor\"\n");
                        break;
                }
                free(childEntry);
                break;
            case 0x05:
                writeString(output, tuples[i].value);
                break;
            case 0x06:
                writeReal(output, tuples[i].value);
                break;
            case 0x07:
                writeBoolean(output, tuples[i].value);
                break;
            default:
                fprintf(output, "\"unknown format: %u\"\n", (unsigned int)tuples[i].format);
                break;
            
        }
        if(i < maxCountInput - 1){
                fprintf_s(output, ",\n");
            }
    }

    free(tuples);
    free(entry);
}


int main(){
    FILE* input;
    FILE* dictionary;
    FILE* output;
    fopen_s(&input, "example.bin", "rb");
    fopen_s(&output, "example.json", "w");
    fopen_s(&dictionary, "C:/Users/Nazar/Documents/BEJ/DSP8010_2023_1/dictionaries/Memory_v1.bin", "rb");

    decode(input, dictionary, output, 7, 1, 1, 12, 0);

    fclose(input);
    fclose(output);
    fclose(dictionary);

}