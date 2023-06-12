#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_DEFNAME_FIRST_CHAR_ALLOWED_CHARS        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
#define TOKEN_DEFNAME_FIRST_CHAR_ALLOWED_CHARS_LEN    53
#define TOKEN_DEFNAME_SPLIT_CHAR_ALLOWED_CHARS        "1234567890_-"
#define TOKEN_DEFNAME_SPLIT_CHAR_ALLOWED_CHARS_LEN    12
#define TOKEN_CHAR_IGNORE                             " \t\n\r"
#define TOKEN_CHAR_IGNORE_LEN                         4
#define TOKEN_CHAR_FIRST_CHAR_INT                     "0123456789"


typedef struct TOKEN_STRUC {
   enum TOKEN_ENUM {
      TOKEN_KEYWORD,             // keyword
      TOKEN_PRIM_STR_DELIM,      // '
      TOKEN_PRIM_STR,            // 'string'
      TOKEN_PRIM_INT,            // 42
      TOKEN_COMM_DELIM,          // `
      TOKEN_COMM,                // `comment`
      TOKEN_EXPR_END,            // ;
      TOKEN_LGROUP,              // (
      TOKEN_RGROUP,              // )
      TOKEN_DIRECTIVE_DELIM,     // #
      TOKEN_DIRECTIVE,           // #DIRECTIVE#
      TOKEN_FN_APPLY,            // .
      TOKEN_LIST_DELIM,          // ,
      TOKEN_DEF_TAGS_DELIM,      // :
      TOKEN_DEF,                 // def:def
      TOKEN_BLOCK_DELIM_START,   // {
      TOKEN_BLOCK_DELIM_END,     // }
      TOKEN_NAMESPACE_DELIM,     // /
      TOKEN_ARRAY_DELIM_START,   // [
      TOKEN_ARRAY_DELIM_END,     // ]
      TOKEN_DEF_SET,             // =
      TOKEN_EOF,                 // \0
    } type;

    char* value;
} token_t;

token_t* token_init(int type, char* val);

int char_could_start_keyword(char* character);
int char_could_split_keyword(char* character);
int char_could_start_int(char* character);
int char_can_ignore(char* character);


#endif
