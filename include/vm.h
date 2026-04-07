#ifndef VM_H_
#define VM_H_

#include <stdint.h>

#define MEMORY_SIZE 65536

typedef enum
{
    OP_HALT = 0x00,
    OP_PUSH = 0x01,
    OP_POP = 0x02,
    OP_ADD = 0x03,
    OP_SUB = 0x04,
} OpCode;

typedef struct
{
    uint8_t memory[MEMORY_SIZE];
    uint16_t PC;
    uint16_t SP;
    uint8_t R[4];
} VM;

void vm_init(VM *vm);
void vm_run(VM *vm);

#endif