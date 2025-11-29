#include "rom.h"
#include "cpu.h"  

sROM ROM[] = {
    {"0x12", movRV},
    {"0x11", jmpln},
    {"0x03", interupt},
};
