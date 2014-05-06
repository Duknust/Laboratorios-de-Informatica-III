#include <string.h>
#include "util.h"

void clear_str(char * array, int lenght) {
    int i;
    for (i = 0; i < lenght; i++)
        array[i] = '\0';
}

char * trim(char* str) {
    while(isspace(*str)) 
        str++;

    return str;
}
