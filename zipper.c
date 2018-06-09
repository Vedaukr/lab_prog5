#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "archivator.h"

int main(int argc, char ** argv){
    FILE * input = NULL;
    FILE * output = NULL;
    
    if(argc > 2){
       
        

        //Compression
        if(strcmp(argv[1], "c") == 0){
            input = fopen(argv[2], "rb");
            char * out = malloc( (strlen(argv[2]) + 5) * sizeof(char));
            strcpy(out, argv[2]);
            strcat(out, ".cmp");
            output = fopen(out, "w+b");
            if (output == NULL || input == NULL) {
                printf("Can't open files\n'"); return 0;
            }
                        
            compress(input, output, argv[2]);
            free(out);
            fclose(input);
            fclose(output);
        }

        //Decompression
        else if(strcmp(argv[1], "d") == 0){
            input = fopen(argv[2], "rb");
            if (input == NULL) {
                printf("Can't open files\n'"); return 0;
            }
            
            decompress(input);
            fclose(input);            
        }

        else{
            printf("Wrong key, c for compression, d for decompression\n");
        }

    }

}