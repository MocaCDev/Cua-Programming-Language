#ifndef TOKEN // macro checker ifndef checks if the macro name TOKEN is not defined: ifndef = if not defined
#define TOKEN // This is just so that we don't run into errors for including this header file in multiple other files!
#include <stdlib.h>
#include <string.h>

typedef struct TOKENS {
    enum {
        TOKEN_ID,
        TOKEN_TYPE_INT,
        TOKEN_LOCAL,
        TOKEN_EQUALS,
        TOKEN_SEMI,
        TOKEN_EOF, // END OF FILE has been reached when this is the current token
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_STRING,
        TOKEN_INT_ASSIGNMENT,
        TOKEN_STRING_ASSIGNMENT
    } TOKEN_TYPE; // a enum is ideals that have a number assigned to it. starts at zero by default
    char* value;
} TOKEN_S; // since this is 'typedef struct', all we do is: TOKENS tokens;

TOKEN_S* init_token(int type, char* value);

#endif