#include "vm.h"

#include <stdio.h>

int main(void)
{
    VM vm;

    vm_init(&vm);

    vm.memory[0] = 0x42;

    vm_run(&vm);

    printf("Done\n");

    return 0;
}
