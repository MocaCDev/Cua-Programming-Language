#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

parser* init_parser(LEXER_* lexer) {
    parser* parser = calloc(1,sizeof(parser));

    parser->lexer = lexer;
    parser->current_token = next_token(lexer);
    parser->last_token = parser->current_token;

    return parser;
}