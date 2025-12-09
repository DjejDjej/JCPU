#define _POSIX_C_SOURCE 200809L
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

int getSplitedCode(char *code) {

  char *token;
  char *delim = " ";
  char *next = NULL;
  int count = 0;
  char **out_code; 
  token = strtok_r(code, delim, &next);
  while (token != NULL) {
    if (token[strlen(token) - 1] == '\n') {
      count++;
    }
    printf("%s ", token);
    out_code[count] = realloc(out_code[count], count);
    strcpy(out_code[count], token);
    token = strtok_r(NULL, delim, &next);
  }

  for (int i = 0; i < count; i++) {
    // printf("%s", out_code[count]);
  }

  free(out_code);
  return 0;
}

int main(int argc, char **argv) {

  if (argc > 2) {

    char *res = getFileContent(argv[1]);
    // writeResult(argv[2], res);
    getSplitedCode(res);
    free(res);

  } else {
  }
}
