#include "lexer.h"
#include "tokens.h"
#include "function_shortcuts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// sets up LEXER_ struct
LEXER_* init_lexer(char* contents, TOKEN_S* tokens) {
    LEXER_* lexer = calloc(1,sizeof(*lexer));

    lexer->i = 0;
    lexer->contents = contents;
    lexer->type_declaration = (char*) malloc(sizeof(lexer->type_declaration));
    lexer->line = 1;
    lexer->is_default = 1;
    lexer->is_int = 1;
    lexer->is_string = 1;
    lexer->is_local_variable = 1; // 1 as in false. No local variable declaration found yet

    // Setting up TOKEN_S struct in the lexer struct
    //lexer->tokens = malloc(sizeof(*tokens)); // we had to allocate the size of the the tokens argument(declared in main.c)  
    lexer->tokens = tokens;

    lexer->current_char = lexer->contents[lexer->i];

    return lexer;
}

static inline void gather_comment(LEXER_* lexer) {
    while(1) {
        advance(lexer);

        if(lexer->current_char == '\n') return advance(lexer);
        if(lexer->current_char == '\0') return;
    }
}

static inline TOKEN_S* check(LEXER_* lexer, char* value, char* is_value, int tokenize_as) {
    if(strcmp(value,is_value)==0) {
        lexer->tokens = init_token(tokenize_as,value);
        return lexer->tokens;
    } else {
        lexer->tokens = init_token(TOKEN_ID,value);
        return lexer->tokens;
    }
}

static inline void gather_multi_line_comment(LEXER_* lexer) {
    while(1) {
        advance(lexer);

        if(lexer->current_char == '[') {
            advance(lexer);

            if(isalnum(lexer->current_char)) {
                gather_id(lexer);
                
                if(strcmp(lexer->tokens->value,"INLINECODE")==0) {

                    if(lexer->current_char==']') advance(lexer);
                    else {
                        fprintf(stderr,"\nError: Missing closing ']' on line %d\n\n",lexer->line);
                        fflush(stderr);
                        exit(EXIT_FAILURE);
                    }

                    if(lexer->current_char=='{') {
                        advance(lexer);

                        if(lexer->current_char=='\n') advance(lexer);

                        lexer->is_default = 0;
                        skip_whitespace(lexer);

                        if(lexer->current_char == '}') {
                            advance(lexer);
                            if(lexer->current_char=='[') {
                                advance(lexer);

                                if(isalnum(lexer->current_char)) gather_id(lexer);

                                if(strcmp(lexer->tokens->value,"END")==0) {
                                    if(lexer->current_char == ']') advance(lexer);
                                    else {
                                        RAISE_ERROR("\nMissing closing ']' to inline-comment-block-code closing statement\n\n",1);
                                    }
                                } else {
                                    RAISE_ERROR("\nMissing 'END' to closing statement of the inline-comment-block-code\n\n",1);
                                }
                            }
                        }
                        else {
                            RAISE_ERROR("\nMissing closing '}' to inline-comment-block-code\n\n",1);
                        }
                    }
                }
            }
            /*
            if(lexer->current_char == ']') {
                    advance(lexer);
            } else {
                fprintf(stderr,"\nMissing closing ']' to inline-comment-block-code\n\n");
                fflush(stderr);
                exit(EXIT_FAILURE);
            }*/
            continue;
        }
        
        if(lexer->current_char == '-') {
            advance(lexer);
            if(lexer->current_char == '/') {
                return advance(lexer);
                //if(lexer->current_char == '\n') {
                    //return advance(lexer);
                //}
            } else {
                RAISE_ERROR("\nWas expecting end of multi line comment on line %d\n\n",1,lexer->line);
            }
        }
    }
}

static inline void* gather_ids(LEXER_* lexer) {
    char* value = calloc(1,sizeof(char));

    while(isalnum(lexer->current_char)) {
        char* current = get_char_as_string(lexer);

        value = realloc(
            value,
            strlen(current)*sizeof(char*)
        );

        strcat(value,current);
        advance(lexer);
        if(lexer->current_char == ' ') break;
        free(current);
    }
    
    /*
        We are going to tokenize keywords in the lexer.
        This function, gather_id, will get the keyword, and we will then store it in the lexer struct
        so that we can then tokenize them!
    */
    lexer->tokens = init_token(TOKEN_ID, value);

    return lexer;
}

/* This function is slightly different than gather_ids */
static inline void gather_string(LEXER_* lexer) {
    char* string_value = calloc(1,sizeof(char));

    do {

        char* curr = get_char_as_string(lexer);

        string_value = realloc(
            string_value,
            strlen(curr)*sizeof(char*)
        );
        strcat(string_value,curr);

        advance(lexer);
        if(lexer->current_char == '"') {
            lexer->tokens = init_token(TOKEN_STRING_ASSIGNMENT,string_value);
            return advance(lexer);
        }
    } while(1);
}

static inline void* gather_var_name(LEXER_* lexer) {
    char* var_name = calloc(1,sizeof(char));

    while(1) {
        var_name = realloc(
            var_name,
            strlen(get_char_as_string(lexer))*sizeof(char*)
        );
        strcat(var_name,get_char_as_string(lexer));
        advance(lexer);
        if(lexer->current_char == ' ') break;
    }
    return var_name;
}

void get_variable_name(LEXER_* lexer) {
    skip_whitespace(lexer);

    lexer->variable_name = gather_var_name(lexer);
    lexer->tokens = init_token(TOKEN_ID,lexer->variable_name);
}

static inline int gather_int_assignment(LEXER_* lexer) {
    char* val = calloc(1,sizeof(char));
    
    do {
        char* cur = get_char_as_string(lexer);

        val = realloc(
            val,
            strlen(cur)*sizeof(char*)
        );
        strcat(val,cur);

        advance(lexer);
    } while(isdigit(lexer->current_char));

    return atoi(val);
}

// Gets the next ideal 'token'. This is dependable upon the switch statement(could be a character, could be multiple characters, could be a symbol etc). This is used heavily in parser.c
TOKEN_S* next_token(LEXER_* lexer) {
    while(lexer->current_char != '\0' && lexer->i < strlen(lexer->contents)) {
        if(lexer->current_char == ' ' || lexer->current_char == 10)
            skip_whitespace(lexer);
        
        if(lexer->current_char=='-') {
            advance(lexer);
            if(lexer->current_char=='-') {
                gather_comment(lexer);
                continue;
            } else {
                RAISE_ERROR("\nExpecting single line comment, '--', found '-'.\n\n",1);
            }
            continue;
        }
        if(lexer->current_char == '/') {
            advance(lexer);
            if(lexer->current_char == '-') {
                gather_multi_line_comment(lexer);
                continue;
            } else {
                RAISE_ERROR("\nWas expecting multi-line comment on line %d.\n\n",1,lexer->line);
            }
            continue;
        }

        if(lexer->current_char == '\n') advance(lexer);
        if(lexer->current_char == '"') {
            if(lexer->is_int == 1) /*This will get more advanced when we introduce string, char, bit, float and double*/ {
                advance(lexer);

                if(!(lexer->current_char == '"')) gather_string(lexer);
                else RAISE_ERROR("\nExpecting string got NULL instead",-1);

                return lexer->tokens;
            } else RAISE_ERROR("\nCannot have string assignment for integer type(line %d)\n\n", -1, lexer->line);
        }

        if(isdigit(lexer->current_char)) {
            // ToDo: Pick up integer assignments
            /*do {
                printf("%c",lexer->current_char);
                advance(lexer);
            } while(isdigit(lexer->current_char));*/
            int a = gather_int_assignment(lexer);
            char* number = (char*) malloc(sizeof(char*));
            sprintf(number, "%d", a);
            lexer->tokens = init_token(TOKEN_INT_ASSIGNMENT, number);

            return lexer->tokens;
        }
        
        if(isalnum(lexer->current_char)) {
            gather_id(lexer);
        }

        if(strcmp(lexer->tokens->value,"local")==0) {
            lexer->tokens = init_token(TOKEN_LOCAL,lexer->tokens->value);
            lexer->is_local_variable = 0;

            // advance(lexer);

            return lexer->tokens;
        }
        if(strcmp(lexer->tokens->value,"int")==0) {
            lexer->tokens = init_token(TOKEN_TYPE_INT,lexer->tokens->value);

            lexer->is_int = 0;

            memcpy(lexer->type_declaration,lexer->tokens->value,strlen(lexer->tokens->value)+1); // setting type_declaration to "int"

            // advance(lexer);
            /*
            // Should be variable name..
            get_variable_name(lexer);
            */
            return lexer->tokens;
        }
        
        switch(lexer->current_char) {
            case '=': return advance_with_token(lexer,init_token(TOKEN_EQUALS,get_char_as_string(lexer)));
            case ';': return advance_with_token(lexer, init_token(TOKEN_SEMI,get_char_as_string(lexer)));
            default: break;
        }
    }

    return init_token(TOKEN_EOF,"\0"); // guess the end of the file has been reached
}

//LEXER_* gather_type(LEXER_* lexer, int type_id) {
//}
// Gets the next character as long as the next character isn't '\0'
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
    int i = 0;
    do {
        advance(lexer);
        i++;

        if(i > 2 && lexer->is_default == 1) {
            fprintf(stdout,"\n\033[1;35mWarning: Uneeded ammount of spaces on line %d\n\n\033[0m",lexer->line);
            fflush(stdout);
            i = 0;
        }
    } while(lexer->current_char == ' ' || lexer->current_char == 10);
}

// This 'tokenizes' the recently found token, using init_token. TOKEN_TYPE is then set to the token found in the switch statement in next_token
TOKEN_S* advance_with_token(LEXER_* lexer, TOKEN_S* tokens) {
    advance(lexer);
    lexer->tokens = tokens;
    return tokens;
}

// I kinda just copied this from what I did with my language. This, to me, is the easiest way to do this
TOKEN_S* gather_id(LEXER_* lexer) {
    //char* value = calloc(1,sizeof(char));

    //while(isalnum(lexer->current_char)) {
        //char* current = get_char_as_string(lexer);

        //value = realloc(
            //value,
            //strlen(current)*sizeof(char)
        //);

        //strcat(value,current);
        //advance(lexer);
    //}
    
    /*
        We are going to tokenize keywords in the lexer.
        This function, gather_id, will get the keyword, and we will then store it in the lexer struct
        so that we can then tokenize them!
    */
    //lexer->tokens = init_token(TOKEN_ID, value);

    gather_ids(lexer);

    return lexer->tokens;
}
char* get_char_as_string(LEXER_* lexer) {
    char* string = calloc(2,sizeof(char));

    string[0] = lexer->current_char;
    string[1] = '\0';

    return string;
}