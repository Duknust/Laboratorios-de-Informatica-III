#include <string.h>
#include "util.h"

void clear_str(char * array, int lenght) {
    int i;
    for (i = 0; i < lenght; i++)
        array[i] = '\0';
}

char * trim(const char* str) {
    int i=0, len = strlen(str);
    char * tmp =str;
    while(isspace(*str)) 
        str++;

    return str;
}
