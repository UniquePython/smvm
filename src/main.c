#include "vm.h"
#include "assembler.h"

#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        fprintf(stderr, "Cannot open %s\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    char *buf = malloc(len + 1);
    fread(buf, 1, len, f);
    buf[len] = '\0';

    fclose(f);
    return buf;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input.asm>\n", argv[0]);
        return 1;
    }

    VM vm;

    vm_init(&vm);

    char *src = read_file(argv[1]);

    assemble(src, &vm);

    vm.PC = 0;

    vm_run(&vm);

    return 0;
}
