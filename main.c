#include <stdio.h>
#include <stdlib.h>
#include "src/rf.h"
#include "src/lexer.h"
//#include "src/primary.h"
#include "src/parser.h"

int main(int args, char **argv)
{
    if(args < 2)
    {
        fprintf(stderr, "Expected filename");
        exit(EXIT_FAILURE);
    }

    char *data = read_file(argv[1]);
    Lexer *lex = __init__(data);
    Token *t = lex_next(lex);
    parser_pickup(t, lex);
}