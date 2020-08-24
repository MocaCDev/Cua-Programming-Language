#ifndef FILE_READER
#define FILE_READER
#include <stdlib.h>

typedef struct FILE_BUFFER {
    size_t buffer_size;
    size_t ammount_of_character;
} file_buffer;

char* read_file(const char* file_to_read);

#define ASSERT_FILE_BUFFER_SIZE(size, match) ( ((size & match) < size) ? 0 : 1 )

#endif