#include "inst.h"
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int pc;

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

int decodeLine(const char *line) {
  if (line == NULL) {
    return 1;
  }
  int pos = 0;
  char *line_cp = strdup(line);
  char *saveptr;
  char *tok = strtok_r(line_cp, " ", &saveptr);
  inst s = {};
  char *inst = "";
  char *arg1 = "";
  char arg1_type;

  char *arg2 = "";
  char arg2_type;

  while (tok != NULL) {

    if (pos == 0) {
      inst = tok;
    } else if (pos == 1) {
      arg1 = tok;
    } else if (pos == 2) {
      arg2 = tok; // todo add support for load.
    }

    pos++;
    tok = strtok_r(NULL, " ", &saveptr);
  }

  arg1_type = getArgType(arg1, strlen(arg1) - 1);
  arg2_type = getArgType(arg2, strlen(arg2) - 1);

  arg1 = removeChars(arg1, arg1_type, strlen(arg1));
  arg2 = removeChars(arg2, arg2_type, strlen(arg2));
  s = getInst(inst, arg1_type, arg2_type);

  if (strcmp(s.asm_name, "null") == 0) {
    
    printf("Error couldnt find a inst %s\n",inst);
  }
  if (strlen(arg1) != s.arg1_size ) {
    printf("Error wrong size of params in %s arg1 %s -> expected size -> %i recieved size -> %zu\n",inst,arg1,s.arg1_size,strlen(arg1));
    free(line_cp);
    return 1;
  }
if(strlen(arg2) != s.arg2_size ){

    printf("Error wrong size of params in %s arg2 %s -> expected size -> %i recieved size -> %zu\n",inst,arg2,s.arg2_size,strlen(arg2));
    free(line_cp);
    return 1;


}
  s.arg1 = arg1;
  s.arg2 = arg2;
  pc+= INST_SIZE;
  pc+= s.arg1_size;
  pc+= s.arg2_size;
  printf("%s %s %s \n",s.hex_name,s.arg1,s.arg2);

  free(arg1);
  free(arg2);
  free(line_cp);
  return 0;
}

int getSplitedCode(const char *code) {
  char *code_cp = strdup(code);
  char *saveptr;

  char *tok = strtok_r(code_cp, "\n", &saveptr);
  while (tok) {
    decodeLine(tok);
    tok = strtok_r(NULL, "\n", &saveptr);
  }

  free(code_cp);
  return 0;
}

int main(int argc, char **argv) {

  if (argc > 2) {
    pc = 0;
    char *res = getFileContent(argv[1]);
    getSplitedCode(res);
  }
}
