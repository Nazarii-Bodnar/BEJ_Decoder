#include "BEJDecoder.h"
#include "stdio.h"

int generateJSON(bejTuple* source, int sourceLength, FILE* output){
    for(int i = 0; i < sourceLength; i++){
        if(source[i].format == 0x00 || source[0].format == 0x01){
            //recursive call for array or set
        }
        else{
            
        }
    }
}

int main(){
    return 1;
}