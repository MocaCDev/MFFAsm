#include "lexer.h"

// Keywords that require a '.'
static const char *MAIN_KEYWORDS[] = {
  "target", "SET_STACK", "align_msp"
};

static const char *target_k = "target";
static const char *targets[] = {
  "LINUX", "LOCAL", "WIN"
};

static const char *set_stack_k = "SET_STACK";
static const char *align_k = "align_msp";

static inline int is_main_k(char *word)
{
    for(int i = 0; i < sizeof(MAIN_KEYWORDS) / sizeof(char*); i++)
    {
        if(cmp_str(word, (char*)MAIN_KEYWORDS[i]) == 0)
            return 0;
    }

    return 1;
}

static inline char *cts(char c)
{
    char *str = calloc(2, sizeof(char));
    str[0] = c;
    str[1] = '\0';

    return str;
}

static inline Lexer *skip_whitespace(Lexer *lex)
{
    while(lex->data[lex->index] == ' ')
    {
        lex->index++;
    }

    return lex;
}

static inline char *pickup_word(Lexer *lex)
{
    char *word = calloc(1, sizeof(char));
    int size = 0;

    while(!(lex->data[lex->index] == ' ') && !(lex->data[lex->index] == '\0'))
    {
        if(lex->data[lex->index] == '\n')
            break;
        word[size] = lex->data[lex->index];
        word = realloc(
            word,
            (size + 2) * sizeof(char)
        );
        size++;
        lex->index++;
    }
    return word;
}

static inline Token *init_token(char *val, int type)
{
    Token *t = calloc(1, sizeof(*t));

    t->tt = type;
    t->token_value = val;
    return t;
}

Lexer *__init__(char *data)
{
    Lexer *lex = calloc(1, sizeof(*lex));

    lex->data = data;
    lex->index = 0;
    lex->length = str_len(data);
    lex->last_char = lex->data[lex->index];

    return lex;
}

Token *lex_next(Lexer *lex)
{
    while(lex->index < lex->length && !(lex->data[lex->index] == '\0'))
    {
        if(is_ascii(lex->data[lex->index])==0 || isdigit(lex->data[lex->index]))
        {
            char *word = pickup_word(lex);
      
            if(is_main_k(word) == 0) 
            {
                if(!(lex->last_char == '.'))
                {
                    fprintf(stderr, "LEXER_ERROR:\n\tExpected `.` before %s", word);
                    exit(EXIT_FAILURE);
                }

                if(cmp_str(word, (char*)target_k)==0)
                    return init_token(word, TOKEN_TARGET_K);
                if(cmp_str(word, (char*)set_stack_k)==0)
                    return init_token(word, TOKEN_SET_STACK_K);
                if(cmp_str(word, (char*)align_k) == 0)
                    return init_token(word, TOKEN_ALIGN_K);
            } else {
                return init_token(word, TOKEN_WORD);
            }
        }
        if(lex->data[lex->index] == ' ')
        {
            lex = skip_whitespace(lex);
            continue;
        }

        lex->last_char = lex->data[lex->index];
        lex->index++;
    }

    return init_token("\0", TOKEN_EOF);
}