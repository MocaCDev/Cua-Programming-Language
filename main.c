#include <stdio.h>
#include <stdlib.h>
#include "src/parser.h"
#include "src/lexer.h"
#include "src/tokens.h"
#include "src/file_reader.h"

// RUN COMMAND: ./main.o examples/example.cua
// CUA's programming language source code can now be found on GitHub. Let me know if you need me to publish it on another website!

// Keywords 'local' and 'int' are now tokenized and the variable name is picked up as well!

int main(int argc, char* args[]) {

    TOKEN_S* tokens = calloc(1,sizeof(TOKEN_S*));
    LEXER_* lexer = init_lexer(
        read_file(args[1]),
        tokens
    );
    parser* parser = init_parser(lexer);

    return 0;
}
