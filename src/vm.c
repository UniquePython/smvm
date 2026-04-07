#include "vm.h"

#include <string.h>
#include <inttypes.h>
#include <stdio.h>

void vm_init(VM *vm)
{
    memset(vm, 0, sizeof(*vm));

    vm->SP = 0xFFFF;
}

void vm_run(VM *vm)
{
    while (1)
    {
        uint8_t val = vm->memory[vm->PC];
        printf("%" PRIu8 "\n", val);
        break;
    }
}