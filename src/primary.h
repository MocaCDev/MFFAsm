#pragma once
#include <stdlib.h>

#define MAX_STACK_SIZE 0xFFFF0

typedef struct stack_entries
{
    long int address;
    char *entry_data;
    
    // If sub-entries are within the stack, will be placed here
    union {
        struct stack_entries **sub_entries;
    } SubEntries;
} _stack_entries;

typedef struct registers
{
    union {
        //long int address;
        _stack_entries *pointer;
    } MBP;
    union {
        //long int address;
        _stack_entries *pointer;
    } MSP;
} Registers;

typedef struct stack
{
    long int stack_size;
    Registers *regs;
    _stack_entries **entries;
    
    union {
        // Top of the stack
        long int limit;
        // Where the stack is cut off from the rest of the stack being used
        long int base;
    } UnusedStack;
    union
    {
        // Where MBP is placed
        long int limit;
        // Where MSP is placed
        long int base; // always zero, normally
    } UsedStack;
} Stack;

Stack *__init_stack__(long int MSP_place, long int MBP_place);
//Stack *__refernish(long int new_MSP_place, long int new_MBP_place);

//#endif