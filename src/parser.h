#ifndef PARSER
#define PARSER
#include "tokens.h"
#include "lexer.h"
#include "tree.h"

typedef struct PARSER_ {
    LEXER_* lexer;
    TOKEN_S* token;
    TOKEN_S* last_token;

    
} parser;

parser* init_parser(LEXER_* lexer);
SYN_TREE_* parse(parser* parser);
SYN_TREE_* local_variable_definition(parser* parser);

#endif