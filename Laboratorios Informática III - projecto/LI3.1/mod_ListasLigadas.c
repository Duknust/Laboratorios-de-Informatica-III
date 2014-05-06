#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mod_ListasLigadas.h"
#include "estruturas.h"

LLptr artigos=NULL;

LLptr returnArtigos(){
    return artigos;
}

int insere(Artigo *art, int tipo) {
    LLptr tmp;

    tmp = (LLptr) malloc(sizeof (LL));
    tmp->tipo = tipo;
    tmp->elem = art;
    tmp->seg = artigos;
    tmp->nElems=0;
    tmp->ant = NULL;


    if (artigos != NULL) {
        tmp->nElems = artigos->nElems;
        artigos->ant = tmp;
    }
    artigos = tmp;
    artigos->nElems++;

    return 0;
}

int remover(Artigo *art) {
    LLptr tmp;
    int flag = 0;
    if (art == NULL)
        return -1;

    tmp = artigos;

    do {
        if ((tmp->tipo == CONFE) &&
                (tmp->elem != NULL) &&
                (art->inteiro == tmp->elem->inteiro)) {
            if (tmp->ant != NULL)
                tmp->ant->seg = tmp->seg;
            if (tmp->seg != NULL)
                tmp->seg->ant = tmp->ant;
            flag = 1;
            tmp = NULL;
        } else
            tmp = tmp->seg;
    } while (tmp != NULL && flag == 0);

    free(tmp);
}

void imprimeElems() {
    LLptr tmp = artigos;


    while (tmp) {
        printf("%d -- %s\n", tmp->elem->tipoArt, tmp->elem->inteiro);
        tmp = tmp->seg;
    }
}

int comprimento(LLptr lst) {
    LLptr copia = NULL;
    int cnt = 0;
    for (copia = lst; copia->seg != NULL; copia = copia->seg)
        cnt++;

    return cnt;
}