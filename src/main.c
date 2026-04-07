#include "vm.h"

#include <stdio.h>

int main(void)
{
    VM vm;

    vm_init(&vm);

    vm.memory[0] = 0x01;
    vm.memory[1] = 0x05;

    vm.memory[2] = 0x01;
    vm.memory[3] = 0x03;

    vm.memory[4] = 0x03;

    vm.memory[5] = 0x02;

    vm.memory[6] = 0x00;

    vm_run(&vm);

    printf("Done\n");

    return 0;
}
