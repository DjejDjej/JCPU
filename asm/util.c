
#define _POSIX_C_SOURCE 200809L
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strSlice(const char *str, int start, int num_chars) {
  if (num_chars <= 0) {
    return NULL;
  }

  size_t len = strlen(str);
  if ((size_t)(start + num_chars) > len) {
    return NULL;
  }

  char *output = malloc(num_chars + 1);
  if (!output)
    return NULL;

  memcpy(output, str + start, num_chars);
  output[num_chars] = '\0';

  return output;
}


