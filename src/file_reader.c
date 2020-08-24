#include "file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(const char* file_to_read) {
    char* buffer = 0;
    long length;

    int index = 0;
    char* extension = calloc(1,sizeof(char));

    for(;index < strlen(file_to_read); index++) {
        if(file_to_read[index] == '.') {
            while(file_to_read[index] != '\0') {
                char* value = calloc(1,sizeof(char));

                value[0] = file_to_read[index];
                value[1] = '\0';

                extension = realloc(extension,strlen(value));
                strcat(extension,value);
                index++;
            }
        }
    }
    
    if(strcmp(extension,".cua")==0) {
        FILE* file = fopen(file_to_read,"rb");

        if(!(file)) {
            printf("\n\nErr reading file: %s\n\n",file_to_read);
            exit(1);
        }

        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = calloc(length, length);
        if(buffer) {
            fread(buffer,1,length,file);
        }

        fclose(file);
    } else {
        fprintf(stderr, "\nUnknown file type: %s\n\n",extension);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }

    return buffer;
}