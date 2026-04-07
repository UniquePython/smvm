#include "assembler.h"

#include <ctype.h>
#include <string.h>

void next_token(const char *src, int *pos, Token *out)
{
    // skip whitespace
    while (src[*pos] == ' ' || src[*pos] == '\t' || src[*pos] == '\n' || src[*pos] == '\r')
        (*pos)++;

    // skip comments (# to end of line)
    if (src[*pos] == '#')
    {
        while (src[*pos] != '\n' && src[*pos] != '\0')
            (*pos)++;

        next_token(src, pos, out);
        return;
    }

    // end of source
    if (src[*pos] == '\0')
    {
        out->type = TOKEN_EOF;
        return;
    }

    // number
    int val = 0;
    if (isdigit(src[*pos]))
    {
        while (src[*pos] != '\n' && src[*pos] != '\0' && isdigit(src[*pos]))
        {
            val = val * 10 + (src[*pos] - '0');
            (*pos)++;
        }

        out->type = TOKEN_NUMBER;
        out->as.value = val;

        return;
    }

    // word
    int i = 0;
    if (isalpha(src[*pos]))
    {
        while (isalpha(src[*pos]) && src[*pos] != '\0')
            out->as.text[i++] = src[(*pos)++];

        out->as.text[i] = '\0';
        out->type = TOKEN_WORD;

        return;
    }
}

void assemble(const char *src, VM *vm)
{
    Token out = {0};
    int pos = 0;

    while (1)
    {
        next_token(src, &pos, &out);

        switch (out.type)
        {
        case TOKEN_WORD:
            const char *instr = out.as.text;

            if (strcmp(instr, "HALT") == 0)
                vm->memory[vm->PC++] = OP_HALT;
            else if (strcmp(instr, "PUSH") == 0)
            {
                vm->memory[vm->PC++] = OP_PUSH;

                Token operand;
                next_token(src, &pos, &operand);
                vm->memory[vm->PC++] = (uint8_t)operand.as.value;
            }
            else if (strcmp(instr, "POP") == 0)
                vm->memory[vm->PC++] = OP_POP;
            else if (strcmp(instr, "ADD") == 0)
                vm->memory[vm->PC++] = OP_ADD;
            else if (strcmp(instr, "SUB") == 0)
                vm->memory[vm->PC++] = OP_SUB;
            else
                break;

            break;

        case TOKEN_EOF:
            return;

        default:
            break;
        }
    }
}