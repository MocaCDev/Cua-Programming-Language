#ifndef LEXER
#define LEXER
#include "tokens.h"

typedef struct Lexer {
    char* contents;
    char* variable_name;
    unsigned int i; // this will be the current character we are on
    unsigned int line;
    unsigned int is_local_variable; // this will be set to 0(true) if the "local" variable was found
    char current_char;
    TOKEN_S* tokens;
} LEXER_;

LEXER_* init_lexer(char* contents, TOKEN_S* tokens);
LEXER_* gather_type();
TOKEN_S* next_token(LEXER_* lexer);
TOKEN_S* advance_with_token(LEXER_* lexer, TOKEN_S* tokens);
TOKEN_S* gather_id(LEXER_* lexer);
void advance(LEXER_* lexer);
void skip_whitespace(LEXER_* lexer);
char* get_char_as_string(LEXER_* lexer);
void get_variable_name(LEXER_* lexer);

#endif