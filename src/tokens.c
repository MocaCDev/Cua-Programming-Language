#include "tokens.h"
#include <stdlib.h>

TOKEN_S* init_token(int type) {
    TOKEN_S* token = calloc(1,sizeof(token));

    token->TOKEN_TYPE = type;

    return token;
}