#include "util.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "cpu.h"


int16_t hexStrToInt16(const char *str) {
  char *endptr = NULL;
  errno = 0;

  // Parse as hexadecimal
  unsigned long val = strtoul(str, &endptr, 16);

  // Validate: no errors, entire string consumed, and fits in int16_t
  if (errno != 0 || *endptr != '\0' || val > 0xFFFF) {
    printf("Invalid hex input for int16_t: \"%s\"\n", str);
    return 0;
  }

  // Interpret the 16-bit value as signed
  if (val & 0x8000) {
    // Negative number in two's complement
    return (int16_t)(val - 0x10000);
  }

  // Positive number
  return (int16_t)val;
}

uint8_t hexStrToUint8(const char *str) {
  char *endptr = NULL;
  errno = 0;

  // Parse as hexadecimal
  unsigned long val = strtoul(str, &endptr, 16);

  // Validate: no errors, entire string consumed, and fits in uint8_t
  if (errno != 0 || *endptr != '\0' || val > 0xFF) {
    printf("Invalid hex input for uint8_t: \"%s\"\n", str);
    return 0; // Or handle error differently
  }

  return (uint8_t)val;
}

int hexStrToInt(char *str) { return (int)strtol(str, NULL, 16); }

char *strSlice(const char *str, int start, int num_chars) {
    if (num_chars <= 0) {
        return NULL;
    }

    size_t len = strlen(str);
    if ((size_t)(start + num_chars) > len) {
        return NULL;
    }

    char *output = malloc(num_chars + 1);
    if (!output) return NULL;

    memcpy(output, str + start, num_chars);
    output[num_chars] = '\0';   


    return output;
}






void throwError(int code, char *func){

if(code == 0){

printf("load from memory wasnt sucessful at %s ",func);
}

if(code == 1){

printf("unable to get instruction at func %s",func);
exit(0);

}

if(code == 2){

printf("WRITING PAST OUTSIDE A MEMORY at func %s",func);
exit(0);

}


}


