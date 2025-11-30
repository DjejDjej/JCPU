#include "rom.h"
#include "cpu.h"

sROM ROM[] = {

    // 0D - printer
    // 0E - interupt var
    // 0F - PC

//   inst  cfunc     arg1 arg2
    {"03", interupt, 0, 0},
    {"11", jmpln,    2, 0},
    {"12", movRV,    2, 2},
    {"13", movRR,    2, 2},
    {"14", movVM,    2, 4},
    {"15", movRM,    2, 4},
    {"16", movMR,    4, 2},
    {"31", addRR,    2, 2},
    {"32", subRR,    2, 2},
    {"33", inc,      2, 0},
    {"34", dec,      2, 0},
    {"41", push,     2, 0},
    {"42", pop,      2, 2},
};
