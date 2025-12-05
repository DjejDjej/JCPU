#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "util.h"
#include "mem.h"

/* ============================================================
   MEMORY MAP (64 KB TOTAL)
   ------------------------------------------------------------
   $0000 – $7EFF   RAM (program memory + variables)
   $7F00 – $7FFF   STACK (256 bytes, grows downward)
   $8000 – $80FF   I/O PORTS (memory-mapped hardware, 256 bytes)
   $8100 – $FFFF   ROM (not used yet, reserved for future firmware)
   ============================================================ */
    
    // 0D - printer
    // 0E - interupt var


/* ============================================================
   FLAGS
   ------------------------------------------------------------
    0 - Zero
    1 - Carry
    2 - Negative
    3 - Overflow

   ============================================================ */



uint8_t RAM[RAM_SIZE];
uint8_t STACK[STACK_SIZE];
uint8_t IO[IO_SIZE];
uint8_t ROM[ROM_SIZE];

instSets instSet[] = {
//   inst  cfunc     arg1 arg2
    {"01", load,     6, 0},
    {"03", interupt, 0, 0},
    {"11", jmpln,    2, 0},
    {"12", movRV,    2, 2},
    {"13", movRR,    2, 2},
    {"14", movVM,    2, 4},
    {"15", movRM,    2, 4},
    {"16", movMR,    4, 2},
    {"31", addRR,    2, 2},
    {"32", subRR,    2, 2},
    {"33", inc,      2, 0},
    {"34", dec,      2, 0},
    {"41", push,     2, 0},
    {"42", pop,      2, 0},
};



int initMEM() {
  for (size_t i = 0; i < RAM_SIZE; i++) {
    RAM[i] = 0;
  }
  for (size_t i = 0; i < STACK_SIZE; i++) {
    STACK[i] = 0;
  }
  for (size_t i = 0; i < IO_SIZE; i++) {
    IO[i] = 0;
  }
  for (size_t i = 0; i < ROM_SIZE; i++) {
    ROM[i] = 0;
  }
  return 0;
}


void testMEM() {

  int globalCount = 0;
  int value = 120;
  for (int i = 0; i < RAM_SIZE; i++) {
    char *hexAddr = malloc(8);
    char *hexAddr_i = malloc(8);
   
    if (value >= 255){value =120;}
    
    snprintf(hexAddr, 5, "%X", globalCount);
    snprintf(hexAddr_i, 5, "%X", value++);

    if (memOp(1, hexAddr, hexAddr_i) != 0) {
      printf("ERROR at %s", hexAddr);

      if (RAM[i] != memOp(0, hexAddr, "")) {

        printf("ERROR value at %s", hexAddr);
      }
    }
    globalCount++;
    fflush(stdout);
  }

for (int i = 0; i < STACK_SIZE; i++) {
    char *hexAddr = malloc(8);
    char *hexAddr_i = malloc(8);
   
    if (value >= 255){value =120;}
    
    snprintf(hexAddr, 5, "%X", globalCount);
    snprintf(hexAddr_i, 5, "%X", value++);

    if (memOp(1, hexAddr, hexAddr_i) != 0) {
      printf("ERROR at %s", hexAddr);

      if (STACK[i] != memOp(0, hexAddr, "")) {

        printf("ERROR value at %s", hexAddr);
      }
    }
    globalCount++;
    fflush(stdout);
  }

for (int i = 0; i < IO_SIZE; i++) {
    char *hexAddr = malloc(8);
    char *hexAddr_i = malloc(8);
   
    if (value >= 255){value =120;}
    
    snprintf(hexAddr, 5, "%X", globalCount);
    snprintf(hexAddr_i, 5, "%X", value++);

    if (memOp(1, hexAddr, hexAddr_i) != 0) {
      printf("ERROR at %s", hexAddr);

      if (IO[i] != memOp(0, hexAddr, "")) {

        printf("ERROR value at %s", hexAddr);
      }
    }
    globalCount++;
    fflush(stdout);
  }
for (int i = 0; i < ROM_SIZE; i++) {
    char *hexAddr = malloc(8);
    char *hexAddr_i = malloc(8);
   
    if (value >= 255){value =120;}
    
    snprintf(hexAddr, 5, "%X", globalCount);
    snprintf(hexAddr_i, 5, "%X", value++);

    if (memOp(1, hexAddr, hexAddr_i) != 0) {
      printf("ERROR at %s", hexAddr);

      if (ROM[i] != memOp(0, hexAddr, "")) {

        printf("ERROR value at %s", hexAddr);
      }
    }
    globalCount++;
    fflush(stdout);
  }

  fflush(stdout);
  printf("TEST IS DONE ");
  }

  void showMEM() {

    int globalCount = 0;
    for (int i = 0; i < RAM_SIZE; i++) {
      if (RAM[i] != 0) {
        printf("MemAddr -> %i Value -> %i\n", i, RAM[i]);
      }
      globalCount++;
      fflush(stdout);
    }

    for (int i = 0; i < STACK_SIZE; i++) {
      if (STACK[i] != 0) {
        printf("StackAddr-> %i Value -> %i\n", i, STACK[i]);
      }

      globalCount++;
      fflush(stdout);
    }
    for (int i = 0; i < IO_SIZE; i++) {
      if (IO[i] != 0) {
        printf("IO Addr-> %i Value -> %i\n", i, IO[i]);
      }

      globalCount++;
      fflush(stdout);
    }

    for (int i = 0; i < ROM_SIZE; i++) {
      if (ROM[i] != 0) {
        printf("ROM Addr-> %i Value -> %i\n", i, ROM[i]);
      }

      globalCount++;
      fflush(stdout);
    }
  }

  int memoryBus(char *addS) {
    int add = hexStrToInt(addS);

    if (add >= RAM_START && add < RAM_SIZE+ RAM_START) {

      return 0;
    } else if (add >= STACK_START && add < STACK_START + STACK_SIZE ) {

      return 1;
    } else if (add >= IO_START && add < IO_START + IO_SIZE) {

      return 2;
    } else if (add >= ROM_START && add < ROM_START + ROM_SIZE) {

      return 3;
    } else {

      return -1;
    }

    return -1;
  }





uint8_t memOp(int op, char *add, char *value) {
    int addr = hexStrToInt(add);
    int memType = memoryBus(add);
    uint8_t *current = NULL;
    int offset = 0;
    int regionSize = 0;

    switch (memType) {
        case 0: // RAM
            current = RAM;
            offset = RAM_START;
            regionSize = RAM_SIZE;
            break;

        case 1: // STACK
            current = STACK;
            offset = STACK_START;
            regionSize = STACK_SIZE;
            break;

        case 2: // IO
            current = IO;
            offset = IO_START;
            regionSize = IO_SIZE;
            break;

        case 3: // ROM
            current = ROM;
            offset = ROM_START;
            regionSize = ROM_SIZE;
            break;

        default:
            throwError(2, "memOP"); // unknown mem type
            return 0;
    }

    int pos = addr - offset;

    if (pos < 0 || pos >= regionSize) {
        
   fflush(stdout);
	printf("%x",pos);
	throwError(2, "memOP");
        return 0;
    }

    // READ
    if (op == 0) {
        return current[pos];
    }

    // WRITE
    else if (op == 1) {
        current[pos] = hexStrToInt(value);
        return 0;
    }
    fflush(stdout);
    printf("%x",pos);
    throwError(2, "memOP");
    return 0;
}


