#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    The parser basically just sets up the syntax of the language.

    Before adding in any built in methods we have a lot of updating to do.
    For one, we need to implement the runtime(or ast) into the project.
    After that, we need to figure out how to store valuable information(variable names etc) into the ast struct(or whatever we call it)
    After that, we need to figure out how the parser is going to approach built-in methods(such as print)
    We need the parser to setup the runtime. There shoud be NO output within the parser, meaning we are
    going to need to build the runtime inside the parser and then start a seperate file that basically 'configures'
    the language and does the rest of the work(Such as getting input, sending output, opening files etc).
    The runtime setup will happen in the parser.
    The actuall runtime step itself will happen in runtime.c and it will be the key of the 'magic' that makes our language work!

    P.S: The runtime is a very big step in the usage of the print statement. Not only that,
    but in order for us to even get/store variable names/assignments we are going to need to start building the runtime.
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

    if(parser_->token->TOKEN_TYPE == TOKEN_LOCAL) {
        parser_ = parser_gather_next_token(parser_, TOKEN_LOCAL);

        get_variable_name(parser_->lexer);

        if(strcmp(parser_->token->value,"int")==0) {
            parser_gather_next_token(parser_, TOKEN_TYPE_INT);


            if(strlen(parser_->lexer->variable_name)>0) {
                if(parser_->token->TOKEN_TYPE == TOKEN_EQUALS) {
                    parser_gather_next_token(parser_,TOKEN_EQUALS);

                    // While it does print the variable name and value, notice how the value is stored in the token struct. We don't want that. We want it inside the runtime. So, while this works, it is very VERY incorrect.
                    printf("%s=%s\n",parser_->lexer->variable_name,parser_->token->value);

                    parser_gather_next_token(parser_, TOKEN_INT_ASSIGNMENT);
                }
            }
            parser_->lexer->is_int = 1;
            if(parser_->token->TOKEN_TYPE == TOKEN_SEMI) parser_gather_next_token(parser_, TOKEN_SEMI);
            
        }
    }

    if(!(parser_->token->TOKEN_TYPE == TOKEN_EOF)) return parse(parser_);
    else return parser_;
}