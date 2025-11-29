#include "cpu.h"
#include "ram.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO find Memory Leak:
char **getCode(FILE *file) {

  fseek(file, 0L, SEEK_END);
  int c;
  int lines = 0;
  int c_index = 0;
  int len = ftell(file);
  if (len == 0) {
    return NULL;
  }
  char **code = malloc(len);
  char *str_buf = malloc(len);
  rewind(file);
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n' || c_index * lines == len) {
      str_buf[c_index] = '\0';
      code[lines] = malloc(sizeof(str_buf) + 8);
      if (c_index != 0) {
        strcpy(code[lines++], str_buf);
      }
      strcpy(str_buf, "");
      c_index = 0;
    } else {
      str_buf[c_index++] = c;
    }
  }
  return code;
}

// TODO fix \n

int identifyInstructions(char *srcLine) {
  if (!srcLine)
    return -1;

  // Copy the line safely
  char *Line = malloc(strlen(srcLine) + 1);
  strcpy(Line, srcLine);

  // Allocate an array of 3 pointers for tokens
  char **code = malloc(3 * sizeof(char *));
  if (!code) {
    free(Line);
    return -1;
  }

  int pos = 0;
  char *token = strtok(Line, " ");

  while (token != NULL && pos < 3) {
    // Allocate memory for each token including null terminator
    code[pos] = malloc(strlen(token) + 1);
    strcpy(code[pos], token);
    pos++;

    token = strtok(NULL, " ");
  }

  // Fill remaining slots with NULL if fewer than 3 tokens
  for (int i = pos; i < 3; i++) {
    code[i] = NULL;
  }

  execInst(code);

  // Free all allocated memory
  free(Line);

  return 0;
}

int main(int argc, char **argv) {

  initCPU();
  initRAM();
  if (argc > 0) {
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
      return 1;
    }
    char **code = getCode(file);
    if (code == NULL) {
      return 1;
    }
    int line_count = 0;
    while (1) {
      if (code[line_count] == NULL || *code[line_count] == '\0') {
        break;
      }
      line_count++;
    }

    while (end == 0) {
      if (registers[15] < line_count) {
        identifyInstructions(code[registers[15]]);
        registers[15]++;
      }
    }
  }

  return 0;
}
