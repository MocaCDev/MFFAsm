#include "primary.h"

Stack *__init_stack__(long int MSP_place, long int MBP_place)
{
    Stack *s = calloc(1, sizeof(*s));
    
    s->stack_size = MAX_STACK_SIZE;
    s->entries = calloc(MAX_STACK_SIZE, sizeof(*s->entries));
    
    long int address = 0;
    for(int i = 0; i < MAX_STACK_SIZE; i++)
    {
        s->entries[i] = calloc(1, sizeof(*s->entries[i]));
        
        s->entries[i]->address = address;
        s->entries[i]->entry_data = (void*)0;
        
        address++;
    }
    
    s->regs = calloc(1, sizeof(*s->regs));
    s->regs->MBP.pointer = s->entries[MBP_place];
    s->regs->MSP.pointer = s->entries[MSP_place];
    
    s->UnusedStack.limit = s->stack_size;
    s->UnusedStack.base = (MBP_place + 1);
    s->UsedStack.limit = MBP_place;
    s->UsedStack.base = MSP_place;
    
    return s;
}