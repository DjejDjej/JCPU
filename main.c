#include "cpu.h"
#include "mem.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *getRawCode(FILE *file) {

  fseek(file, 0L, SEEK_END);

  long int res = ftell(file);
  char *buffer = malloc(res + 1);
  rewind(file);
  char ch;
  size_t i = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (ch != ' ' && ch != '\n' && ch != '\0')
      buffer[i++] = ch;
  }
  buffer[i] = '\0';
  return buffer;
}

instSets *getInst(char *inst) {

  for (size_t i = 1; i < INST_COUNT; i++) {
    if (strcmp(instSet[i].hex, inst) == 0) {
      return &instSet[i];
    }
  }
  return &instSet[0];
}

int execCode(FILE *file) {
  char *raw_code = getRawCode(file);
  int code_len = strlen(raw_code);
  if (code_len % 2 != 0) {
    printf("propably wrong code, odd number of bytes \n");
    halt = 1;
  }

  while (!halt) {
    fflush(stdout);
    if (pc >= strlen(raw_code)) {
      continue;
    }

    char *inst = strSlice(raw_code, pc, INST_SIZE);
    instSets *s = getInst(inst);

    if (strcmp(s->hex,"00") == 0) {
      printf("Wrong instruction at %i [%x] - instruction -> %s\n", pc+1, pc+1, inst);
      halt = 1;
    }
    pc += INST_SIZE;

    char *arg1 = strSlice(raw_code, pc, s->arg1_s);
    pc += s->arg1_s;

    char *arg2 = strSlice(raw_code, pc, s->arg2_s);

    if (strcmp(s->hex, "01") == 0) {
      char *tmp = strSlice(arg1, 4, 2);
      int ln = hexStrToInt(tmp);
      free(arg2);
      arg2 = strSlice(raw_code, pc, ln);
      s->arg2_s = strlen(arg2);
      free(tmp);
    }
    // showMEM();
    pc += s->arg2_s;
    s->exec(arg1, arg2);
    free(inst);
    free(arg1);
    free(arg2);
  }

  free(raw_code);
  return 1;
}

int main(int argc, char **argv) {

  if (argc > 0) {
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL) {
      return 1;
    }

    initCPU();
    initMEM();
    resetFlags();

    execCode(file);
    fclose(file);
  }

  return 0;
}
