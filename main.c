#include <stdio.h>
#include <stdlib.h>
#include "src/parser.h"
#include "src/lexer.h"
#include "src/tokens.h"
#include "src/file_reader.h"
#include "src/tree.h"
#include "src/runtime.h"

// RUN COMMAND: ./main.o examples/example.cua
// CUA's programming language source code can now be found on GitHub. Let me know if you need me to publish it on another website!

int main(int argc, char* args[]) {

    /*if(argc < 2) {
        fprintf(stderr,"\nError: CUA's compiler expects the following command:\n./main.o <filename>\n\n");
        fflush(stderr);
        exit(EXIT_FAILURE);
    }*/

    TOKEN_S* tokens = calloc(1,sizeof(TOKEN_S*));
    char* main_file_path = gather_main_jang_file();
    LEXER_* lexer = init_lexer(
        read_file(main_file_path),
        tokens
    );
    parser* parser = init_parser(lexer);
    SYN_TREE_* syn_tree = parse(parser);
    _RUNTIME_* runtime = init_runtime(lexer, parser);

    //void* b = (int*)10;

    //free(tokens);

    return 0;
}
