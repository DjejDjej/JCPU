#include "rom.h"
#include "cpu.h"  

sROM ROM[] = {
   
    {"0x03", interupt}, //reg 14-1 reg 13 what to print
    {"0x12", movRV},
    {"0x13", movRR}, 
    {"0x11", jmpln},
    
    {"0x31", addRR},
    {"0x32", subRR},
    {"0x33", inc},
    {"0x34", dec},
};
