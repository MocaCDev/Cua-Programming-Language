#ifndef LEXER
#define LEXER
#include "tokens.h"

typedef struct Lexer {
    char* type;
    char* contents;
    unsigned int i; // this will be the current character we are on
    unsigned int line;
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
void gather_comment(LEXER_* lexer);
void gather_multi_line_comment(LEXER_* lexer);

#endif