#include "file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file(const char* file_to_read) {
    char* buffer = 0;
    long length;

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

    return buffer;
}