#ifndef RUNTIME
#define RUNTIME
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>

typedef struct RUNTIME_ {
    SYN_TREE_** variable_definitions;
    size_t amount_of_variable_definitions;
    LEXER_* lexer;
    parser* parser_;
} _RUNTIME_;

_RUNTIME_* init_runtime(LEXER_* lexer, parser* parser_);

#endif