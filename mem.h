#ifndef mem_h
#include <stdint.h>
#define mem_h
typedef struct {
  char *hex;
  int (*exec)(char *, char *);
  int arg1_s;
  int arg2_s;
} sROM;

int initRAM(void);
#define RAM_SIZE 65536
extern uint8_t RAM[RAM_SIZE];
extern sROM ROM[];

#define ROM_SIZE 12
#define INST_SIZE 2

#endif
