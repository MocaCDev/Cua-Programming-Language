#include "tokens.h"
#include <stdlib.h>
#include <string.h>

const char* LOCAL_KEYWORD = "local";

TOKEN_S* init_token(int type, char* value) {
    TOKEN_S* token = calloc(1,sizeof(token));

    token->TOKEN_TYPE = type;
    token->value = value;

    return token;
}