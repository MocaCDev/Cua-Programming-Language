#include "runtime.h"
#include "lexer.h"
#include "parser.h"

_RUNTIME_* init_runtime(LEXER_* lexer, parser* parser_) {
    _RUNTIME_* runtime = calloc(1,sizeof(*runtime));

    runtime->amount_of_variable_definitions = 0;
    runtime->variable_definitions = (void*)0;
    runtime->lexer = lexer;
    runtime->parser_ = parser_;

    return runtime;
}