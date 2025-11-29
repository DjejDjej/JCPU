#ifndef cpu_h
#define cpu_h
#include <stdint.h>
int movRV(char *value1, char *value2);
int interupt(char *value1, char *value2);
int execInst(char **code);
int initCPU();
//instructions
int jmpln(char *loc, char *NaN);
int addRR(char *desReg, char *srcReg);
int movRR(char *desReg, char *srcReg);
int addRR(char *desReg, char *srcReg);
int subRR(char *desReg, char *srcReg);
int inc(char *reg, char *n);
int dec(char *reg, char *n);
//instructions
#define REG_COUNT 16
extern uint8_t registers[REG_COUNT];
extern int end;
#endif
