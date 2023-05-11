#ifndef TOKEN_H
#define TOKEN_H


typedef struct TOKEN_STRUC {
   enum {
      TOKEN_KEYWORD,             // keyword
      TOKEN_STR_DELIM,           // '"'
      TOKEN_STR,                 // "string"
      TOKEN_COMM_DELIM_START,    // '['
      TOKEN_COMM,                // '[comment]'
      TOKEN_COMM_DELIM_END,      // ']'
      TOKEN_DEFINE_CONST,        // '=>'
      TOKEN_DEFINE_MUT,          // '->'
      TOKEN_END,                 // ';'
      TOKEN_LORD,                // '('
      TOKEN_RORD,                // ')'
      TOKEN_DIRECTIVE_DELIM,     // '#'
      TOKEN_DIRECTIVE,           // #DIRECTIVE;
      TOKEN_EOF,                 // '\0'
    } type;

    char* value;
} token_t;

extern token_t* token_init(int type, char* value);


#endif
