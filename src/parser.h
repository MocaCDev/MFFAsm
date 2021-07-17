#pragma once
#include "lexer.h"
#include "primary.h"

typedef struct _parser
{
  Lexer *lex;
  Token *curr_token;
} _Parser;

void parser_pickup(Token *t, Lexer *lex);

//#endif