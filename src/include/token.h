#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
   enum {
      TOKEN_ID,       // keyword
      TOKEN_EQ,       // '='
      TOKEN_STR,      // "string"
      TOKEN_SEMI,     // ';'
      TOKEN_LORD,     // '/'
      TOKEN_RORD,     // '\'
      TOKEN_AMP,      // '&'
      TOKEN_LBRAK,    // '['
      TOKEN_RBRAK,    // ']'
      TOKEN_POUND,    // '#''
      TOKEN_TILDE     // '~'
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif
