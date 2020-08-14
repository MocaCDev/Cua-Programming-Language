#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

parser* init_parser(LEXER_* lexer) {
    parser* parser = calloc(1,sizeof(parser));

    parser->lexer = lexer;
    parser->token = next_token(lexer);
    parser->last_token = parser->token;

    return parser;
}