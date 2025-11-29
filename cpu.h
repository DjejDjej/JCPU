#ifndef cpu_h 
#define cpu_h
#include <stdint.h>
int movRV(char *value1, char *value2);
int interupt(char *value1, char *value2);
int execInst(char **code);
int initCPU();
int jmpln(char *loc, char *NaN);
#define REG_COUNT 8
extern uint8_t registers[REG_COUNT];
extern int end;
#endif
