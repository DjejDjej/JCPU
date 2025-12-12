#define _POSIX_C_SOURCE 200809L
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *getFileContent(char *in_file) {
  FILE *file = fopen(in_file, "r");

  if (!file)
    return NULL;

  fseek(file, 0, SEEK_END);
  long res = ftell(file);
  rewind(file);

  char *result = malloc(res + 1);
  if (!result)
    return NULL;
  size_t read = fread(result, 1, res, file);
  result[read] = '\0';

  fclose(file);
  return result;
}

int writeResult(char *out_file, const char *result) {
  FILE *file = fopen(out_file, "w");

  fprintf(file, result);
  fclose(file);
  return 0;
}

int splitLine(const char *line) {
  if (line == NULL) {
    return 1;
  }

 // projet pismenko po pismneku a nejak rozdelit? idk 

  return 0;
}

int getSplitedCode(const char *code) {
  char *code_cp = strdup(code);
  char *tok = strtok(code_cp, "\n");

  while (tok != NULL) {
    splitLine(tok);
    tok = strtok(NULL, "\n");
  }

  free(code_cp);
  return 0;
}

int main(int argc, char **argv) {

  if (argc > 2) {

    char *res = getFileContent(argv[1]);
    getSplitedCode(res);
  }
}
