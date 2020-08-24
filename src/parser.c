#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

/*
    The parser basically just sets up the syntax of the language
*/

parser* init_parser(LEXER_* lexer) {
    parser* parser = calloc(1,sizeof(*parser));

    parser->lexer = lexer;
    parser->token = next_token(lexer);
    parser->last_token = parser->token;

    return parser;
}

// Gathers the next token for the parser
static inline void parser_gather_next_token(parser* parser_, int token_id) {
    if(parser_->token->TOKEN_TYPE == token_id) {
        parser_->last_token = parser_->token;
        parser_->token = next_token(parser_->lexer);
    } else {
        fprintf(stderr, "\nTokenization configure error: Tokens do not match up on line %d\n\n", parser_->lexer->line);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
}

parser* local_variable_definition(parser* parser_) {

    return parser_;
}