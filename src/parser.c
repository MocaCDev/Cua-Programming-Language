#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
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
static inline parser* parser_gather_next_token(parser* parser_, int token_id) {
    if(parser_->token->TOKEN_TYPE == token_id) {
        parser_->last_token = parser_->token;
        parser_->token = next_token(parser_->lexer);
    } else {
        fprintf(stderr, "\nTokenization configure error: Tokens do not match up on line %d\n\n", parser_->lexer->line);
        fflush(stderr);
        exit(EXIT_FAILURE);
    }
    return parser_;
}

parser* parse(parser* parser) {
    switch(parser->token->TOKEN_TYPE) {
        case TOKEN_LOCAL: return local_variable_definition(parser);
        default: break;
    }
    return parser;
}

parser* local_variable_definition(parser* parser_) {

    if(strcmp(parser_->token->value, "local")==0) {
        parser_ = parser_gather_next_token(parser_, TOKEN_LOCAL);

        get_variable_name(parser_->lexer);
        printf("%s",parser_->lexer->variable_name);

        if(strcmp(parser_->token->value,"int")==0) {
            parser_gather_next_token(parser_, TOKEN_TYPE_INT);


            if(strlen(parser_->lexer->variable_name)>0) {
                if(parser_->token->TOKEN_TYPE == TOKEN_EQUALS) {
                    parser_gather_next_token(parser_,TOKEN_EQUALS);
                    parser_gather_next_token(parser_, TOKEN_INT_ASSIGNMENT);
                }
            }
            parser_->lexer->is_int = 1;
            if(parser_->token->TOKEN_TYPE == TOKEN_SEMI) parser_gather_next_token(parser_, TOKEN_SEMI);
        }
    }

    return parser_;
}