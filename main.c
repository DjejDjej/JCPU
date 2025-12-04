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

  for (size_t i = 0; i < INST_COUNT; i++) {
    if (strcmp(instSet[i].hex, inst) == 0) {
      return &instSet[i];
    }
  }
  
  printf("HERE??? %s\n",inst);
  throwError(1, "getInst");
  return NULL;
}

int execCode(FILE *file) {
// int count = 0;
char *raw_code = getRawCode(file);
  while (1) {
    fflush(stdout);
    if (PC >= strlen(raw_code)) {
      continue;
    }
    char *inst = strSlice(raw_code, PC, INST_SIZE);
    instSets *s = getInst(inst);
    PC += INST_SIZE;

    char *arg1 = strSlice(raw_code, PC, s->arg1_s);
    PC += s->arg1_s;

    char *arg2 = strSlice(raw_code, PC, s->arg2_s);

    if (strcmp(s->hex, "01") == 0) {
      char *tmp = strSlice(arg1, 4, 2);  
      int ln = hexStrToInt(tmp);
      free(arg2); 
      arg2 = strSlice(raw_code, PC, ln);
      s->arg2_s = strlen(arg2);
      free(tmp);
    }
    // showMEM();
    PC += s->arg2_s;
    s->exec(arg1, arg2);
    free(inst);
    free(arg1);
    free(arg2);
  }
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

    execCode(file);
  }

  return 0;
}
