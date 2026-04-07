#include "assembler.h"

#include <ctype.h>

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