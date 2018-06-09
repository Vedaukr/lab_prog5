#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


#include "file.h"
#include "hash.h"
#include "dict.h"

const int dictionarySize = 4095;

void compress(FILE * input, FILE * output, char * inputname){

    puts("Compressing file... ");

    // long long int counter = 0;
    char * buffer = malloc(30*sizeof(char));
    
    fprintf(output, "%s\n", inputname);
    int bit = 256;

    Dictionary * dict = newDictionary(2048);
    initDict(dict);

    int prefix = fgetc(input);


    if(prefix != EOF){
        
        int current, index;
            while ((current = fgetc(input)) != (unsigned)EOF) { 
                // counter++;

                if ((index = dictSearch(dict, prefix, current)) != -1) prefix = index;
                else { 
                    
                    writeBinary(output, prefix);
                    
                    if (bit < dictionarySize) addDict(dict, newNodeSL(bit, prefix, current));
                    
                    bit++;
                    
                    prefix = current; 
                }

                /* if(counter % 100000 == 0){
                    sprintf(buffer, "%lli", counter);
                    puts(buffer);
                } */
            }
    } 
    
    writeBinary(output, prefix);

    if (leftover > 0) fputc(leftoverBits << 4, output);

    puts("Done");

    freeDictionary(dict);
    free(buffer);

}

int decode(Cell ** dict, int code, FILE * output) {
    
    int character; int temp;

    if (code > 255) { 
        character = lastDict(dict, code);
        temp = decode(dict, prefixDict(dict, code), output); 
    } else {
        character = code; 
        temp = code;
    }

    fputc(character, output);
    return temp;
}

void decompress(FILE * input){

    int bit = 256;

    long long int counter = 0;
    char * buffer = malloc(30*sizeof(char));

    

    Cell ** dict = init();

    puts("Decompressing file... ");

    char temp;
    int len = 0;
    char * outputname = malloc(50*sizeof(char));
    outputname[len] = 'u';
    len++;
    while( (temp = fgetc(input)) != '\n' ){
        outputname[len] = temp;
        len++;
    }

    outputname[len] = '\0';

    FILE * output = fopen(outputname, "w+b"); 

    int previous; int current;

    int firstChar;
    
    previous = readBinary(input);
    
    if (previous < 0) {
        return;
    }
    
    fputc(previous, output);
    
    while ((current = readBinary(input)) >= 0) { 
        counter++;
        if (current >= bit) {
            firstChar = decode(dict, previous, output);
            fputc(firstChar, output); 

        } else firstChar = decode(dict, current, output);
        
        if (bit < dictionarySize) add(dict, bit, previous, firstChar);
        
        bit++;
        
        if(counter % 100000 == 0){
            sprintf(buffer, "%lli", counter);
            puts(buffer);
        }

        previous = current;
    }

    
    puts("Done");

    fclose(output);
    freeDict(dict);

}