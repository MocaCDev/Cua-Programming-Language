#include "tree.h"
#include <stdlib.h>

SYN_TREE_* init_syntax_tree(int SYNT_TREE_TYPE) {
    SYN_TREE_* syntax_tree = calloc(1,sizeof(*syntax_tree));

    syntax_tree->TYPE = SYNT_TREE_TYPE;

    /* LOCAL VAR DEFINITION NAME*/
    syntax_tree->local_var_def_name = (void*)0;
    syntax_tree->local_variable_def_information = (void*)0;

    /* LOCAL VAR NAME */
    syntax_tree->local_var_name = (void*)0;

    /* LOCAL VARIABLE:ST_STRING_ASSIGNMENT:TOKEN_STRING_ASSIGNMENT */
    syntax_tree->local_var_value_string = (void*)0;

    return syntax_tree;
}