#ifndef LEX
#define LEX
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

typedef struct token
{
  enum
  {
    TOKEN_INIT,
    TOKEN_TARGET_K,
    TOKEN_SET_STACK_K,
    TOKEN_WORD,
    TOKEN_EOF
  } tt;

  char *token_value;
} Token;

typedef struct lexer
{
  char *data;
  char last_char;
  size_t length;
  int index;
} Lexer;

Lexer *__init__(char *data);
Token *lex_next(Lexer *lex);


#endif