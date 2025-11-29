#include "ram.h"
#include <stdint.h>
#include <stdio.h>

#define RAM_SIZE 131072

uint8_t RAM[RAM_SIZE];
int initRAM() {
  //
  for (size_t i = 0; i < RAM_SIZE; i++) {
    RAM[i] = 0;
  }

  return 0;
}

