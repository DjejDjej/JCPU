#include "cpu.h"
#include "ram.h"
#include "rom.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t registers[REG_COUNT];

int initCPU() {
  for (int i = 0; i < REG_COUNT; i++) {
    registers[i] = 0;
  }
  return 0;
}

uint8_t hexStrToUint8(const char *str) {
    char *endptr = NULL;
    errno = 0;

    // Parse as hexadecimal
    unsigned long val = strtoul(str, &endptr, 16);

    // Validate: no errors, entire string consumed, and fits in uint8_t
    if (errno != 0 || *endptr != '\0' || val > 0xFF) {
        printf("Invalid hex input for uint8_t: \"%s\"\n", str);
        return 0;   // Or handle error differently
    }

    return (uint8_t)val;
}

int hexStrToInt(char *str) { return (int)strtol(str, NULL, 16); }

//// Instructions

int movRV(char *reg, char *val) {
  uint8_t value = hexStrToUint8(val);
  int regist = hexStrToInt(reg);
  registers[regist] = value;
  return 0;
}

int movRR(char *desReg, char *srcReg) {

  uint8_t value = registers[hexStrToInt(srcReg)];
  int regist = hexStrToInt(desReg);
  registers[regist] = value;
  return 0;
}

int addRR(char *desReg, char *srcReg) {

  uint8_t srcVal = registers[hexStrToInt(srcReg)];
  uint8_t desVal = registers[hexStrToInt(desReg)];
  int regist = hexStrToInt(desReg);
  registers[regist] = srcVal + desVal;
  return 0;
}
int subRR(char *desReg, char *srcReg) {

  uint8_t srcVal = registers[hexStrToInt(srcReg)];
  uint8_t desVal = registers[hexStrToInt(desReg)];
  int regist = hexStrToInt(desReg);
  registers[regist] = desVal - srcVal;
  return 0;
}

int inc(char *reg, char *n) {
  int regist = hexStrToInt(reg);
  registers[regist] = registers[regist] + 1;

  return 0;
}
int dec(char *reg, char *n) {
  int regist = hexStrToInt(reg);
  registers[regist] = registers[regist] - 1;

  return 0;
}

int interupt(char *n, char *nic) {
  switch (registers[14]) {
  case 1:
    printf("%u\n", registers[13]);
    break;
  case 4:
    exit(0);
    break;
  }

  return 0;
}

int jmpln(char *loc, char *NaN) { // label will be used later on.

  registers[15] = atoi(loc);
  return 0;
}
int movVM(char *addr, char *val) {

  RAM[hexStrToInt(addr)] = hexStrToUint8(val);
  return 0;
}
int movRM(char *addr, char *regVal) {
  RAM[hexStrToInt(addr)] = registers[hexStrToInt(regVal)];
  return 0;
}
int movMR(char *addr, char *regVal) {

  registers[hexStrToInt(regVal)] = RAM[hexStrToInt(addr)];
  return 0;
}

//// END Instructions

int execInst(char **code) {
  for (int i = 0; i < ROM_SIZE; i++) {
    if ((strcmp(code[0], ROM[i].hex)) == 0) {
      ROM[i].exec(code[1], code[2]);
      return 0;
    }
  }
  return 1;
}
