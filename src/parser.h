#ifndef PARSER
#define PARSER
#include "lexer.h"

typedef struct PARSER_ {
    LEXER_* lexer;
    TOKEN_S* current_token;
    TOKEN_S* last_token;
} parser;

parser* init_parser();

#endif