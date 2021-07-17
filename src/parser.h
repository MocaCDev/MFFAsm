#ifndef PRS
#define PRS
#include "lexer.h"

typedef struct _parser
{
  Lexer *lex;
  Token *curr_token;
} _Parser;

void parser_pickup(Token *t, Lexer *lex);

#endif