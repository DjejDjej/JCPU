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
int cmpRR(char *reg1, char *reg2);
int cmpRV(char *reg1, char *val2);
int cmpRM(char *reg1, char *mem2);
int cmpMR(char *mem1, char *reg2);
int jz(char *loc, char *NaN);
int jnz(char *loc, char *NaN);
int jc(char *loc, char *NaN);
int jnc(char *loc, char *NaN);
int jm(char *loc, char *NaN);
int jp(char *loc, char *NaN);
int jv(char *loc, char *NaN);
int jnv(char *loc, char *NaN);
int and(char *reg1, char *reg2);
int or (char *reg1, char *reg2);
int xor (char *reg1, char *reg2);
int shl(char *reg1, char *Nan);
int shr(char *reg1, char *Nan);
int man_flag(char *flag, char *val);
int man_inter(char *val, char *NaN);
int call(char *funcPC, char *NaN2);
int ret(char *NaN, char *NaN2);
int hlt(char *n, char *NaN);
void showMem();
int resetFlags();
int printFlags();
// instructions
#define REG_COUNT 16
#define FLAGS_COUNT 4
extern uint8_t registers[REG_COUNT];
extern int pc;
extern _Bool halt;
#endif
