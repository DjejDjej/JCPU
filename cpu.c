#include "cpu.h"
#include "rom.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t registers[REG_COUNT];

int end = 0;
int initCPU() {
  for (int i = 0; i < REG_COUNT; i++) {
    registers[i] = 0;
  }
  return 0;
}

uint8_t strToUint(char *str) {

  char *endptr;
  errno = 0;

  unsigned long val = strtoul(str, &endptr, 10);

  if (errno != 0 || *endptr != '\0' || val > 255) {
    printf("Invalid input for uint8_t\n");
  }

  return (uint8_t)val;
}

int hexStrToInt(char *str) { return (int)strtol(str, NULL, 16); }

//// Instructions

int movRV(char *reg, char *val) {
  uint8_t value = strToUint(val);
  int regist = hexStrToInt(reg);
  registers[regist] = value;
  return 0;
}

int interupt(char *n, char *nic) {

  switch (registers[3]) {
  case 1:
    printf("%u\n", registers[1]);
    break;
  case 4:
    end = 1;
    break;
  }

  return 0;
}

int jmpln(char *loc, char *NaN) { // label will be used later on.
  registers[7] = atoi(loc);
  return 0;
}

//// Instructions

int execInst(char **code) {
  for (int i = 0; i < ROM_SIZE; i++) {
    if ((strcmp(code[0], ROM[i].hex)) == 0) {
      ROM[i].exec(code[1], code[2]);
      return 0;
    }
  }
  return 1;
}
