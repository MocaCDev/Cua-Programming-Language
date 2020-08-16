#include "lexer.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// sets up LEXER_ struct
LEXER_* init_lexer(char* contents, TOKEN_S* tokens) {
    LEXER_* lexer = calloc(1,sizeof(LEXER_*));

    lexer->i = 0;
    lexer->contents = contents;
    lexer->line = 1;

    // Setting up TOKEN_S struct in the lexer struct
    lexer->tokens = malloc(sizeof(tokens)); // we had to allocate the size of the the tokens argument(declared in main.c)  
    lexer->tokens = tokens;

    lexer->current_char = lexer->contents[lexer->i];

    return lexer;
}
// Gets the next ideal 'token'. This is dependable upon the switch statement(could be a character, could be multiple characters, could be a symbol etc). This is used heavily in parser.c
TOKEN_S* next_token(LEXER_* lexer) {
    while(lexer->current_char != '\0' && lexer->i < strlen(lexer->contents)) {
        if(lexer->current_char == ' ' || lexer->current_char == 10)
            skip_whitespace(lexer);
        
        if(isalnum(lexer->current_char))
            return gather_id(lexer);
        
        if(lexer->current_char=='-') {
            advance(lexer);
            if(lexer->current_char=='-') {
                gather_comment(lexer);
            } else {
                fprintf(stderr,"\nExpecting single line comment, '--', found '-'.\n\n");
                fflush(stderr);
                exit(EXIT_FAILURE);
            }
            continue;
        }
        if(lexer->current_char == '/') {
            advance(lexer);
            if(lexer->current_char == '-') {
                gather_multi_line_comment(lexer);
                continue;
            } else {
                fprintf(stderr, "\nWas expecting multi-line comment on line %d.\n\n",lexer->line);
                fflush(stderr);
                exit(EXIT_FAILURE);
            }
            continue;
        }
        
        switch(lexer->current_char) {
            case '=': return advance_with_token(lexer,init_token(TOKEN_EQUALS));
            case '\0': return advance_with_token(lexer,init_token(TOKEN_EOF));
        }
    }

    return init_token(TOKEN_EOF); // guess the end of the file has been reached
}
//LEXER_* gather_type(LEXER_* lexer, int type_id) {
//}
// Gets the next character as long as the next character isn't '\0'
void gather_comment(LEXER_* lexer) {
    while(1) {
        advance(lexer);

        if(lexer->current_char == '\n') {
            return advance(lexer);
        }
    }
}
void gather_multi_line_comment(LEXER_* lexer) {
    while(1) {
        advance(lexer);
        
        if(lexer->current_char == '-') {
            advance(lexer);
            if(lexer->current_char == '/') {
                return advance(lexer);
            } else {
                fprintf(stderr,"\nWas expecting end of multi line comment on line %d\n\n",lexer->line);
                fflush(stderr);
                exit(EXIT_FAILURE);
            }
        }
    }
}
void advance(LEXER_* lexer) {
    if(!(lexer->i >= strlen(lexer->contents) || lexer->current_char == '\0')) {
        lexer->i++;
        lexer->current_char = lexer->contents[lexer->i];

        if(lexer->current_char == '\n')
            lexer->line++;
    }
}
// Skips whitespace. Example, if we had "int   a   =   10;" all the whitespace would be skipped
void skip_whitespace(LEXER_* lexer) {
    static int i = 0;
    if(lexer->current_char == ' ' || lexer->current_char == 10) {
        advance(lexer);
        i++;
    }
    if(i > 2) {
        fprintf(stdout,"\n\033[1;35mWarning: Uneeded ammount of spaces on line %d\n\n\033[0m",lexer->line);
        fflush(stdout);
        i = 0;
    }
}
// This 'tokenizes' the recently found token, using init_token. TOKEN_TYPE is then set to the token found in the switch statement in next_token
TOKEN_S* advance_with_token(LEXER_* lexer, TOKEN_S* tokens) {
    advance(lexer);
    return tokens;
}
// I kinda just copied this from what I did with my language. This, to me, is the easiest way to do this
TOKEN_S* gather_id(LEXER_* lexer) {
    char* value = malloc(sizeof(value));

    while(isalnum(lexer->current_char)) {
        char* current = get_char_as_string(lexer);

        value = realloc(
            value,
            strlen(current)*sizeof(char)
        );

        strcat(value,current);
        advance(lexer);
    }

    return init_token(TOKEN_ID);
}
char* get_char_as_string(LEXER_* lexer) {
    char* string = calloc(2,sizeof(char));

    string[0] = lexer->current_char;
    string[1] = '\0';

    return string;
}