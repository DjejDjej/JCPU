#ifndef util_h
#include <stdint.h>
#define util_h
char *strSlice(const char *str, int start, int num_chars);

uint8_t hexStrToUint8(const char *str);
int16_t hexStrToInt16(const char *str);

void debug(char *message,...);
int hexStrToInt(char *str);
void throwError(int code, char *func);
#endif
