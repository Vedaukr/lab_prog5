#include <stdio.h>

void writeBinary(FILE * output, int code);
int readBinary(FILE * input);

int leftover = 0;
int leftoverBits;

void writeBinary(FILE * output, int code) {
    if (leftover > 0) {
        int previousCode = (leftoverBits << 4) + (code >> 8);
        
        fputc(previousCode, output);
        fputc(code, output);
        
        leftover = 0; // no leftover now
    } else {
        leftoverBits = code & 0xF; // save leftover, the last 00001111
        leftover = 1;
        
        fputc(code >> 4, output);
    }
}

int readBinary(FILE * input) {
    int code = fgetc(input);    
    if (code == EOF){
        return -1;
    }

    if (leftover > 0) {
        code = (leftoverBits << 8) + code;
        
        leftover = 0;
    } else {
        int nextCode = fgetc(input);
        
        leftoverBits = nextCode & 0xF; // save leftover, the last 00001111
        leftover = 1;
        
        code = (code << 4) + (nextCode >> 4);
    }
    
    return code;
}