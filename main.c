#include <stdio.h>
#include <stdlib.h>
#include "src/lexer.h"
#include "src/tokens.h"
#include "src/file_reader.h"
#include "src/parser.h"

// RUN COMMAND: ./main.o examples/example.cua

int main(int argc, char* args[]) {

    TOKEN_S* tokens = calloc(1,sizeof(TOKEN_S*));
    LEXER_* lexer = init_lexer(
        read_file(args[1]),
        tokens
    );
    parser* parser = init_parser(lexer);

    return 0;
}