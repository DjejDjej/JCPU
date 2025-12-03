#include "util.h"
#ifndef mem_h
#include <stdint.h>
#define mem_h
typedef struct {
  char *hex;
  int (*exec)(char *, char *);
  int arg1_s;
  int arg2_s;
  int (*exec3)(char *, char *, char *);
} instSets;

#define RAM_START 0x0000
#define RAM_SIZE 0x7F00 // 0x7F00 bytes (32512 bytes), ends at 0x7EFF

#define STACK_START 0x7F00
#define STACK_SIZE 0x0100 // 0x0100 bytes (256 bytes), ends at 0x7FFF

#define IO_START 0x8000
#define IO_SIZE 0x0100 // 0x0100 bytes (256 bytes), ends at 0x80FF

#define ROM_START 0x8100
#define ROM_SIZE 0x7F00 // 0x8000 bytes (32768 bytes), ends at 0xFFFF

#define MEM_SIZE (ROM_START + ROM_SIZE) 

int initMEM(void);
extern instSets instSet[];

uint8_t memOp(int op, char *add, char *value);
int memoryBus(char *addS);

void testMEM();
void showMEM();

#define INST_COUNT 12
#define INST_SIZE 2

#endif
