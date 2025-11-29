#ifndef ram_h 
#define ram_h 

#include <stdint.h>
int initRAM(void);
#define RAM_SIZE 131072
extern uint8_t RAM[RAM_SIZE];
#endif


