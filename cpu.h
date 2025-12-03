#ifndef cpu_h
#define cpu_h
#include <stdint.h>

int execInst(char **code);
int initCPU();
// instructions
int jmpln(char *loc, char *NaN);
int load(char *len, char *str);
int interupt(char *n, char *nic);
int movRV(char *value1, char *value2);
int movRR(char *desReg, char *srcReg);
int movVM(char *addr, char *val);
int movRM(char *addr, char *regVal);
int movMR(char *addr, char *regVal);
int addRR(char *desReg, char *srcReg);
int subRR(char *desReg, char *srcReg);
int inc(char *reg, char *n);
int dec(char *reg, char *n);
int hexStrToInt(char *str);
int pop(char *value, char *n);
int push(char *value, char *n);
void showMem() ;
// instructions
#define REG_COUNT 16
extern uint8_t registers[REG_COUNT];
extern int PC;
#endif


