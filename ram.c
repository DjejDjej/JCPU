#include "ram.h"
#include <stdint.h>
#include <stdio.h>

#define RAM_SIZE 131072

int initRAM() {
  //
  uint8_t RAM[RAM_SIZE];
  for (size_t i = 0; i < RAM_SIZE; i++) {
    RAM[i] = 0;
  }

  return 0;
}
