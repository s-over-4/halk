#ifndef TOKEN_H
#define TOKEN_H


typedef struct TOKEN_STRUC {
   enum {
      TOKEN_KEYWORD,             // keyword
      TOKEN_STR_DELIM,           // '
      TOKEN_STR,                 // 'string'
      TOKEN_COMM_DELIM,          // `
      TOKEN_COMM,                // `comment`
      TOKEN_EXPR_END,            // ;
      TOKEN_LGROUP,              // (
      TOKEN_RGROUP,              // )
      TOKEN_DIRECTIVE_DELIM,     // #
      TOKEN_DIRECTIVE,           // #DIRECTIVE;
      TOKEN_FN_APPLY,            // .
      TOKEN_LIST_DELIM,          // ,
      TOKEN_DEF_ARGS_DELIM,      // :
      TOKEN_BLOCK_DELIM_START,   // {
      TOKEN_BLOCK_DELIM_END,     // }
      TOKEN_NAMESPACE_DELIM,     // /
      TOKEN_ARRAY_DELIM_START,   // [
      TOKEN_ARRAY_DELIM_END,     // ]
      TOKEN_EOF,                 // \0
    } type;

    char* value;
} token_t;

char TOKEN_DEFNAME_FIRST_CHAR_ALLOWED_CHARS[] = "abcdefghijklmnopqrstuvwxyz_";   // chars that can begin a var name
int  TOKEN_DEFNAME_FIRST_CHAR_ALLOWED_CHARS_LEN = 27; // maximum efficiency!
char TOKEN_DEFNAME_SPLIT_CHAR_ALLOWED_CHARS[] = "1234567890_-";                  // chars that can be in the rest of the var name,
                                                                                 // not including the ones already defined to begin
                                                                                 // one.
int  TOKEN_DEFNAME_SPLIT_CHAR_ALLOWED_CHARS_LEN = 12;
char TOKEN_CHAR_IGNORE[] = " \t\n\r";  // characters to ignore while parsing tokens
int  TOKEN_CHAR_IGNORE_LEN = 4;

int char_could_start_keyword(char* character);
int char_could_split_keyword(char* character);
int char_can_ignore(char* character);


#endif
