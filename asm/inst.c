#define _POSIX_C_SOURCE 200809L
#include "inst.h"
#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


inst instSet[] = {
   //hex   asm         arg1  size type arg2  size type
    {"00", "null",	NULL, 0,   '0', NULL, 0,  '0',},
    {NULL, "label",	NULL, 4,   'A', NULL, 0,  '0',},
    {"12", "mov",	NULL, 2,   'R', NULL, 2,  'V',},
    {"14", "mov",	NULL, 4,   'A', NULL, 2,  'V',},

};



inst getInst(const char *name,const char arg1_type, const char arg2_type) {
  for (size_t i = 0; i < INST_COUNT; i++) {
   inst ins = instSet[i];
    if ((strcmp(ins.asm_name, name) == 0) && ins.arg1_type == arg1_type && ins.arg2_type == arg2_type) {
	    return instSet[i];
    }
  }
  return instSet[0];
}

char getArgType(const char *arg, const int arg_size) {
   if(arg_size <= 0)
    return '0';
   
  if (arg[0] == '[' && arg[arg_size] == ']') 
    return 'A';
  
  if (arg[0] == 'r') 
    return 'R';
  
  return 'V';
}


char *translateReg(const char *arg) { 
 char *tmp= strdup(arg) ;
 char *res = malloc(4);
 if(arg[0] == 'r' && strlen(arg) == 2){
   
   tmp= strSlice(tmp,1,1);

   snprintf(res,3,"0%s",tmp);

   free(tmp);
   return res;
 }

   free(tmp);
  return NULL; 

 }


char *removeChars(const char *arg, char type, int arg_size) {
    char *ret = malloc(arg_size + 1);
    if (!ret) return NULL;

    if (type == 'V') {
        strcpy(ret, arg);
        return ret;
    }

    if (type == 'R') {
        strcpy(ret, arg);
        char *tmp = translateReg(ret);

        if (tmp != ret) {
            free(ret);   
        }
        return tmp;
    }

    if (type == 'A') {
     
	free(ret); 
        return strSlice(arg, 1, arg_size-2);
    }

    free(ret);
    return NULL;
}
