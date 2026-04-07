#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#include "vm.h"

typedef enum
{
    TOKEN_WORD,
    TOKEN_NUMBER,
    TOKEN_EOF,
} Token_Kind;

typedef struct
{
    Token_Kind type;
    union
    {
        char text[64];
        int value;
    } as;
} Token;

void next_token(const char *src, int *pos, Token *out);
void assemble(const char *src, VM *vm);

#endif