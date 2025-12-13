#include "cpu.h"
#include "mem.h"
#include "util.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t registers[REG_COUNT];
uint16_t sp;
uint16_t inter;
_Bool flags[FLAGS_COUNT];
int pc;
_Bool halt = 0;

int initCPU() {
  for (int i = 0; i < REG_COUNT; i++) {
    registers[i] = 0;
  }

  sp = STACK_START + STACK_SIZE;
  pc = 0;

  return 0;
}

//// Instructions

// 00
int null(char *len, char *str) {

  printf("Cannot call non existing instruction \n");
  return 1;
}

// 01
int load(char *len, char *str) {
  char *addS = strSlice(len, 0, 4);
  char *lnS = strSlice(len, 4, 2);
  int add = hexStrToInt(addS); // MAGIC NUMBERS WOHOOOO
  int ln = hexStrToInt(lnS);
  int count = 0;

  for (size_t i = 0; i < ln;) {

    char *buf = strSlice(str, i, 2);
    i += 2;
    char *hexAddr = malloc(5);
    snprintf(hexAddr, 5, "%x", count + add);
    if (memOp(1, hexAddr, buf) != 0) {
      throwError(1, "load");
    }
    free(buf);
    free(hexAddr);
    count++;
  }
  free(addS);
  free(lnS);
  return 0;
}

// 02
int call(char *funcPC, char *NaN2) {
  int this_PC_i = pc;
  char this_PC[5];
  sprintf(this_PC, "%x", this_PC_i);
  push(this_PC, NULL);
  jmpln(funcPC, NULL);
  return 0;
}
// 03
int ret(char *NaN, char *NaN2) {

  char ret_PC[5];

  sprintf(ret_PC, "%x", sp);

  int loc = memOp(0, ret_PC, NULL);
  memOp(1, ret_PC, "00");
  char buff[5];
  sprintf(buff, "%x", loc);

  return 0;
}

// 04
int interupt(char *n, char *nic) {
  switch (inter) {
  case 1:
    printf("%u\n", registers[hexStrToInt("0x0D")]);
    break;
  case 4:
    showMEM();
    exit(0);
    break;
  }

  return 0;
}
int hlt(char *n, char *NaN) {
  halt = 1;
  return 0;
}

// 12
int movRV(char *reg, char *val) {
  uint8_t value = hexStrToUint8(val);
  int regist = hexStrToInt(reg);
  registers[regist] = value;
  return 0;
}

// 13
int movRR(char *desReg, char *srcReg) {

  uint8_t value = registers[hexStrToInt(srcReg)];
  int regist = hexStrToInt(desReg);
  registers[regist] = value;
  return 0;
}
// 31
int addRR(char *desReg, char *srcReg) {

  uint8_t srcVal = registers[hexStrToInt(srcReg)];
  uint8_t desVal = registers[hexStrToInt(desReg)];
  int regist = hexStrToInt(desReg);
  registers[regist] = srcVal + desVal;
  return 0;
}
// 32
int subRR(char *desReg, char *srcReg) {

  uint8_t srcVal = registers[hexStrToInt(srcReg)];
  uint8_t desVal = registers[hexStrToInt(desReg)];
  int regist = hexStrToInt(desReg);
  registers[regist] = desVal - srcVal;
  return 0;
}
// 33
int inc(char *reg, char *n) {
  int regist = hexStrToInt(reg);
  registers[regist] = registers[regist] + 1;

  return 0;
}
// 34

int dec(char *reg, char *n) {
  int regist = hexStrToInt(reg);
  registers[regist] = registers[regist] - 1;

  return 0;
}

// 14
int movMV(char *addr, char *val) {

  if (memOp(1, addr, val) != 0) {
    throwError(1, "movVM");
  };
  return 0;
}

int resetFlags() {

  for (int i = 0; i < FLAGS_COUNT; i++) {
    flags[i] = 0;
  }
  return 0;
}
int printFlags() {

  printf("zero flag %i\n", flags[0]);
  printf("carry flag %i\n", flags[1]);
  printf("neg flag %i\n", flags[2]);
  printf("overflow flag %i\n", flags[3]);
  printf("\n");
  return 0;
}

int cmp(char *arg1, char *arg2) {
  int a1 = hexStrToInt(arg1);
  int a2 = hexStrToInt(arg2);
  int calc = a1 - a2;
  resetFlags();
  if (calc == 0) {
    flags[0] = 1;
  } // Zero

  if ((uint32_t)a1 < (uint32_t)a2) {
    flags[1] = 1;
  } // Carry (unsigned borrow)

  if (calc < 0) {
    flags[2] = 1;
  } // Negative

  if (((a1 ^ a2) & (a1 ^ calc)) < 0)
    flags[3] = 1;

  return 0;
}

// 21
int cmpRV(char *reg1, char *val2) {

  char arg1[3];
  uint8_t arg1_i = registers[hexStrToUint8(reg1)];
  sprintf(arg1, "%x", arg1_i);

  if (cmp(arg1, val2) == 1) {
    return 1;
  }

  return 0;
}

// 22

int cmpRR(char *reg1, char *reg2) {

  char arg1[3];
  uint8_t arg1_i = registers[hexStrToUint8(reg1)];
  sprintf(arg1, "%x", arg1_i);

  char arg2[3];
  uint8_t arg2_i = registers[hexStrToUint8(reg2)];
  sprintf(arg2, "%x", arg2_i);
  cmp(arg1, arg2);
  if (cmp(arg1, arg2) == 1) {
    return 1;
  }

  return 0;
}

// 23
int cmpRM(char *reg1, char *mem2) {

  char arg1[3];
  uint8_t arg1_i = registers[hexStrToUint8(reg1)];
  sprintf(arg1, "%x", arg1_i);

  char arg2[3];
  uint8_t arg2_i = memOp(0, mem2, NULL);
  sprintf(arg2, "%x", arg2_i);

  if (cmp(arg1, arg2) == 1) {
    return 1;
  }

  return 0;
}

// 24

int cmpMR(char *mem1, char *reg2) {

  char arg1[3];
  uint8_t arg2_i = memOp(0, mem1, NULL);
  sprintf(arg1, "%x", arg2_i);

  char arg2[3];
  uint8_t arg1_i = registers[hexStrToUint8(reg2)];
  sprintf(arg2, "%x", arg1_i);

  if (cmp(arg1, arg2) == 1) {
    return 1;
  }

  return 0;
}

// 25
int man_flag(char *flag, char *val) {
  flags[hexStrToInt(flag)] = hexStrToInt(val);

  return 0;
}

// 26
int man_inter(char *val, char *NaN) {
  inter = hexStrToInt(val);

  return 0;
}

// 15
int movRM(char *addr, char *regVal) {
  sprintf(regVal, "%d", 42);

  if (memOp(1, addr, regVal) != 0) {

    throwError(1, "movRM");
  }
  return 0;
}
// 16
int movMR(char *addr, char *regVal) {

  registers[hexStrToInt(regVal)] = memOp(0, addr, "");
  return 0;
}
// 41
int push(char *value, char *n) {

  sp--;
  char buff[5];
  sprintf(buff, "%x", sp);
  if (memOp(1, buff, value) != 0) {
    throwError(1, "push");
  }
  return 0;
}
// 42
int pop(char *dst, char *n) {
  char buff[5];
  sprintf(buff, "%x", sp);
  registers[hexStrToUint8(dst)] = memOp(0, buff, NULL);
  if (memOp(1, buff, "00") != 0) {
    throwError(1, "pop");
  }

  sp++;
  return 0;
}

// 51
int jmpln(char *loc, char *NaN) {
  pc = hexStrToInt(loc);
  return 0;
}

// 52

int jz(char *loc, char *NaN) {

  if (flags[0] == 0) {
    jmpln(loc, NaN);
  }

  return 0;
}

// 53
int jnz(char *loc, char *NaN) {

  if (flags[0] != 0) {
    jmpln(loc, NaN);
  }

  return 0;
}
// 54
int jc(char *loc, char *NaN) {

  if (flags[1] == 0) {
    jmpln(loc, NaN);
  }

  return 0;
}
// 55
int jnc(char *loc, char *NaN) {

  if (flags[1] != 0) {
    jmpln(loc, NaN);
  }

  return 0;
}
// 56
int jm(char *loc, char *NaN) {

  if (flags[2] == 0) {
    jmpln(loc, NaN);
  }

  return 0;
}
// 57
int jp(char *loc, char *NaN) {

  if (flags[2] != 0) {
    jmpln(loc, NaN);
  }

  return 0;
}
// 58
int jv(char *loc, char *NaN) {

  if (flags[3] == 0) {
    jmpln(loc, NaN);
  }

  return 0;
}
// 59
int jnv(char *loc, char *NaN) {

  if (flags[3] != 0) {
    jmpln(loc, NaN);
  }

  return 0;
}

// 61
int and(char *reg1, char *reg2) {

  uint8_t reg1_pos = hexStrToUint8(reg1);

  registers[reg1_pos] = registers[reg1_pos] & registers[reg1_pos];
  return 0;
}

// 62
int or(char *reg1, char *reg2) {

  uint8_t reg1_pos = hexStrToUint8(reg1);

  registers[reg1_pos] = registers[reg1_pos] | registers[reg1_pos];
  return 0;
}

// 63
int xor(char *reg1, char *reg2) {

  uint8_t reg1_pos = hexStrToUint8(reg1);

  registers[reg1_pos] = registers[reg1_pos] ^ registers[reg1_pos];
  return 0;
}

// 64
int shl(char *reg1, char *Nan) {

  uint8_t reg1_pos = hexStrToUint8(reg1);

  registers[reg1_pos] = registers[reg1_pos] << 1;
  return 0;
}

// 65
int shr(char *reg1, char *Nan) {

  uint8_t reg1_pos = hexStrToUint8(reg1);

  registers[reg1_pos] = registers[reg1_pos] >> 1;
  return 0;
}

//// END Instructions
