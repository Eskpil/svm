#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    KEYWORD_PROC,
    KEYWORD_DO,
    KEYWORD_END   
} Keyword;

typedef enum { 
    TOKEN_TYPE_WORD,
    TOKEN_TYPE_INT,
    TOKEN_TYPE_LPAREN,
    TOKEN_TYPE_RPAREN,
    TOKEN_TYPE_LBRACKET,
    TOKEN_TYPE_RBRACKET,
} Token_Type;

// Just to please compiler, this is not any actual code.
typedef struct { 
    size_t loc; 

} Lexer;

#endif
