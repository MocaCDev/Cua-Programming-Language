#ifndef SYNTAX_TREE
#define SYNTAX_TREE

typedef struct SYN_TREE {
    enum {
        ST_DEFAULT, // TOKEN_ID
        ST_LOCAL, // TOKEN_LOCAL
        ST_INT_ASSIGNMENT, // TOKEN_INT_ASSIGNMENT
        ST_STRING_ASSIGNMENT, // TOKEN_STRING_ASSIGNMENT
        ST_EOF
    } TYPE;

    /* LOCAL VARIABLE DEFINITION NAME:ST_LOCAL */
    char* local_var_def_name;
    struct SYN_TREE* local_variable_def_information;

    /* LOCAL VARIABLE NAME:ST_LOCAL */
    char* local_var_name;

    /* LOCAL VARIABLE VALUE:ST_INT_ASSIGNMENT */
    int local_var_value_int;

    /* LOCAL VARIABLE VALUE:ST_STRING_ASSIGNMENT*/
    char* local_var_value_string;
} SYN_TREE_;

SYN_TREE_* init_syntax_tree(int SYN_TREE_TYPE);

#endif