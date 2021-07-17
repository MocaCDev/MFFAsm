#include "parser.h"

#ifdef LEX

static Stack *__refernish(Stack *s, long int new_MSP_place, long int new_MBP_place)
{
    s->regs->MBP.pointer = s->entries[new_MBP_place];
    s->regs->MSP.pointer = s->entries[new_MSP_place];
    
    s->UnusedStack.base = (new_MBP_place + 1);
    
    s->UsedStack.limit = new_MBP_place;
    s->UsedStack.base = new_MSP_place;

    return s;
}

static Stack *align_MSP(Stack *s, long int offset)
{
    long int new_addr = s->regs->MSP.pointer->address - offset;
    
    s->regs->MSP.pointer = s->entries[new_addr];
    s->UsedStack.base = new_addr;
    
    return s;
}

static long int get_int_val(char *val)
{
    if(is_hex(val)==0) return convert(val);
    else return atoi(val);
}

static inline _Parser *get_next(_Parser *p)
{
    p->curr_token = lex_next(p->lex);
    return p;
}

static _Parser *setup_target(Stack *s, _Parser *p)
{
    get_next(p);

    if(!(p->curr_token->tt == TOKEN_WORD))
    {
        fprintf(stderr, "PARSER ERROR:\n\tExpected target value after .target");
        exit(EXIT_FAILURE);
    }
    if(cmp_str(p->curr_token->token_value, "LOCAL")==0)
    {
        printf("Target: %s\n", SYSTEM_TYPE);
    }

    get_next(p);

    return p;
}

static _Parser *set_stack(Stack *s, _Parser *p)
{
    
    get_next(p);
    long int base = get_int_val(p->curr_token->token_value);
    
    get_next(p);
    long int limit = get_int_val(p->curr_token->token_value);
        
    if(limit > MAX_STACK_SIZE)
    {
        limit = MAX_STACK_SIZE;
    }
    
    __refernish(s, base, limit);
    
    get_next(p);
    return p;
}

static _Parser *align_stack_pointer(Stack *s, _Parser *p)
{
    get_next(p);
    
    long int offset = get_int_val(p->curr_token->token_value);

    s = align_MSP(s, offset);
    
    return p;
}

static _Parser *start_parsing(_Parser *p)
{

    Stack *s = __init_stack__(0, 0);
    
    switch(p->curr_token->tt)
    {
        case TOKEN_TARGET_K: setup_target(s, p);
        case TOKEN_SET_STACK_K: set_stack(s, p);
        case TOKEN_ALIGN_K: align_stack_pointer(s, p);
    }
    
    return p;
}

void parser_pickup(Token *t, Lexer *lex)
{
    _Parser *p = calloc(1, sizeof(*p));

    p->lex = lex;
    p->curr_token = t;

    start_parsing(p);
}

#endif