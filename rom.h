#ifndef rom_h 
#define rom_h 
typedef struct {
  char *hex;
  int (*exec)(char *, char *);
} sROM;

extern sROM ROM[];

#define ROM_SIZE 12

#endif
