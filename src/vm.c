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
        OpCode opcode = (OpCode)vm->memory[vm->PC++];

        uint8_t value, a, b;

        switch (opcode)
        {
        case OP_HALT:
            return;

        case OP_PUSH:
            value = vm->memory[vm->PC++];
            vm->memory[--vm->SP] = value;
            break;

        case OP_POP:
            value = vm->memory[vm->SP++];
            printf("%" PRIu8 "\n", value);
            break;

        case OP_ADD:
            a = vm->memory[vm->SP++];
            b = vm->memory[vm->SP++];
            vm->memory[--vm->SP] = a + b;
            break;

        case OP_SUB:
            a = vm->memory[vm->SP++];
            b = vm->memory[vm->SP++];
            vm->memory[--vm->SP] = b - a;
            break;

        default:
            fprintf(stderr, "Unknown opcode\n");
            return;
        }
    }
}