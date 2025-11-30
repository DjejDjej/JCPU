#ifndef rom_h 
#define rom_h 
typedef struct {
  char *hex;
  int (*exec)(char *, char *);
  int arg1_s;
  int arg2_s;
} sROM;

extern sROM ROM[];

#define ROM_SIZE 12
#define INST_SIZE 2

#endif
