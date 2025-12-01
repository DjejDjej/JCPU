#include <stdint.h>
#include <stdio.h>
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
    // 0F - PC



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
    {"42", pop,      2, 2},
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


int memoryBus(char *addS) {
  int add = hexStrToInt(addS);

  if (add >= RAM_START && add <= STACK_START + STACK_SIZE) {

    return 0;
  } else if (add >= STACK_START && add <= STACK_START + STACK_SIZE) {

    return 1;
  } else if (add >= IO_START && add <= IO_START + IO_SIZE) {

   return 2;
  } else if (add >= ROM_START && add <= ROM_START + ROM_SIZE) {

    return 3;
  } else {

    return -1;
  }

  return -1;
}

uint8_t memOp(int op ,char *add, char *value){
int memType = memoryBus(add);
uint8_t *current = NULL; 
int offset = 0;

if(memType == 0) {
current = RAM;
}
if(memType == 1) {
current = STACK;
offset = RAM_SIZE;
}
if(memType == 2) {
current = IO;
offset = RAM_SIZE + STACK_SIZE;
}
if(memType == 3){
current = ROM;
offset = RAM_SIZE + STACK_SIZE + IO_SIZE;
}

if(op == 0  ){
return current[hexStrToInt(add) - offset];
}
if(op == 1 ){
current[hexStrToInt(add) - offset] = hexStrToUint8(value);
return 0;
}
return 0;
}


