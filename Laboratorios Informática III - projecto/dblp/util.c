#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "util.h"

void clear_str(char * array, int lenght) {
    int i;
    for (i = 0; i < lenght; i++)
        array[i] = '\0';
}

char *trim(char* str) {
    char *tmp = NULL;
    int i = 0, j = 0;

    while (isblank(str[i]))
        i++;

    tmp = (char *) calloc((strlen(str) - i + 1), sizeof (char));
    while (i <= strlen(str))
        tmp[j++] = str[i++];

    return tmp;
}

int contemNum(char* str) {
    int i, contem = 0;
    for (i = 1; i < strlen(str) && str[i] != ' '; i++);
    for (++i; i < strlen(str) && !contem; i++)
        if (isdigit(str[i]))
            contem = 1;
    return contem;
}

int contemLet(char* str) {
    int i, contem = 0;
    for (i = 1; i < strlen(str) && !contem; i++) {
        if (isalpha(str[i]))
            contem = 1;
    }
    return contem;
}

void freeStatus(Status* toFree) {
    Status *tmp = toFree;


    while (tmp != NULL) {
        tmp = toFree->seg;
        free(toFree);
    }

}

int numeroAutores(char* listaAut) {
    int i, cont = 0;
    if (!(listaAut == NULL || strcmp("", listaAut) == 0)) {
        for (i = 0; listaAut[i] != '\0'; i++)
            if (listaAut[i] == ',')
                cont++;
        cont++;
    }
    return cont;
}



