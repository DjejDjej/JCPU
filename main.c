#include "cpu.h"
#include "ram.h"
#include "rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *strSlice(char *str, int start, int num_chars) {
  char *output = malloc(num_chars);
  if ((start + num_chars) > strlen(str)) {
    return NULL;
  }
  for (size_t i = 0; i < num_chars; i++) {
    output[i] = str[start + i];
  }
  return output;
}

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

  return buffer;
}

sROM *getInst(char *inst) {

  for (size_t i = 0; i < ROM_SIZE; i++) {
    if (strcmp(ROM[i].hex, inst) == 0) {
      return &ROM[i];
    }
  }

  return NULL;
}

int execCode(FILE *file) {

  char *raw_code = getRawCode(file);
  while (1) {
    fflush(stdout);
    if (registers[hexStrToInt("0x0F")] >= strlen(raw_code)) {
      continue;
    }

    char *inst = strSlice(raw_code, registers[hexStrToInt("0x0F")], INST_SIZE);
    sROM *s = getInst(inst);
    registers[hexStrToInt("0x0F")] += INST_SIZE;
    char *arg1 = strSlice(raw_code, registers[hexStrToInt("0x0F")], s->arg1_s);
    registers[hexStrToInt("0x0F")] += s->arg1_s;
    char *arg2 = strSlice(raw_code, registers[hexStrToInt("0x0F")], s->arg2_s);
    registers[hexStrToInt("0x0F")] += s->arg2_s;
    s->exec(arg1, arg2);
  }
  return 1;
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

    execCode(file);
  }

  return 0;
}
