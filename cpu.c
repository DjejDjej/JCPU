#include "cpu.h"
#include "mem.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t registers[REG_COUNT];
uint16_t sp;

int PC; // NEED TO IMPLEMENT REAL PC

int initCPU() {
  for (int i = 0; i < REG_COUNT; i++) {
    registers[i] = 0;
  }
  sp = STACK_START + STACK_SIZE;
  PC = 0;
  return 0;
}

//// Instructions
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
  // showMEM();
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
// 03
int interupt(char *n, char *nic) {
  switch (registers[hexStrToInt("0x0E")]) {
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

// 11
int jmpln(char *loc, char *NaN) { // label will be used later on.

  PC = hexStrToInt(loc);
  return 0;
}
// 14
int movVM(char *val, char *addr) {

  if (memOp(1, addr, val) != 0) {
    throwError(1, "movVM");
  };
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

//// END Instructions
