#ifndef INST_H
#define INST_H

typedef struct {

  char *hex_name;
  char *asm_name;

  char *arg1;
  int arg1_size;
  char arg1_type;

  char *arg2;
  int arg2_size;
  char arg2_type;

} inst;

// #define INST_COUNT 35

inst getInst(const char *name,const char arg1_type, const char arg2_type) ;
char getArgType(const char *arg, const int arg_size);
char *removeChars(const char *arg, const char type, const int arg_size) ;
#define INST_COUNT 4
#define INST_SIZE 2

#endif
