#include "parser.h"

#ifdef LEX

static inline _Parser *get_next(_Parser *p)
{
  p->curr_token = lex_next(p->lex);
  return p;
}

static _Parser *setup_target(_Parser *p)
{
  get_next(p);

  if(!(p->curr_token->tt == TOKEN_WORD))
  {
    fprintf(stderr, "PARSER ERROR:\n\tExpected target value after .target");
    exit(EXIT_FAILURE);
  }
  if(cmp_str(p->curr_token->token_value, "LOCAL")==0)
  {
    printf("TYPE: %s\n", SYSTEM_TYPE);
  }

  get_next(p);

  return p;
}

static _Parser *set_stack(_Parser *p)
{
  get_next(p);
  printf("BASE: %s\n", p->curr_token->token_value);
  get_next(p);
  printf("LIMIT: %s\n", p->curr_token->token_value);
}

static _Parser *start_parsing(_Parser *p)
{
  switch(p->curr_token->tt)
  {
    case TOKEN_TARGET_K: setup_target(p);
    case TOKEN_SET_STACK_K: set_stack(p);
  }
}

void parser_pickup(Token *t, Lexer *lex)
{
  _Parser *p = calloc(1, sizeof(*p));

  p->lex = lex;
  p->curr_token = t;

  start_parsing(p);
}

#endif