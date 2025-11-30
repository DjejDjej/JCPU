#include "cpu.h"
#include "mem.h"
#include "util.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t registers[REG_COUNT];
uint16_t sp;

int initCPU() {
  for (int i = 0; i < REG_COUNT; i++) {
    registers[i] = 0;
  }
  sp = SP_START;
  return 0;
}

//// Instructions

int load(char *len, char *str) {
  printf("%s %s", len, str);
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
int movVM(char *addr, char *val) {

  RAM[hexStrToInt(addr)] = hexStrToUint8(val);
  return 0;
}
// 15
int movRM(char *addr, char *regVal) {
  RAM[hexStrToInt(addr)] = registers[hexStrToInt(regVal)];
  return 0;
}
// 16
int movMR(char *addr, char *regVal) {

  registers[hexStrToInt(regVal)] = RAM[hexStrToInt(addr)];
  return 0;
}
// 41
int push(char *value, char *n) {

  sp--;
  RAM[sp] = hexStrToUint8(value);
  // inspectMem();
  return 0;
}
// 42
int pop(char *dst, char *n) {

  registers[hexStrToUint8(dst)] = RAM[sp];
  RAM[sp] = 0;
  sp++;
  // inspectMem();
  return 0;
}

//// END Instructions
