#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"
#include "mod_ListasLigadas.h"
#include "funcoes_processamento.h"
#include "filehandling.h"

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

int menorAno(LL *art) {
    LL *tmp = art;
    int i, minimo = -1; // porque de certeza que não existe este ano e muito menos maior
    if (tmp != NULL) minimo = tmp->elem->ano;
    tmp = tmp->seg;
    for (i = 0; tmp != NULL; i++) {
        if (tmp->elem->ano < minimo)
            minimo = tmp->elem->ano;
    }
    return minimo;
}

int tamanhoLL(LL *art) {
    LL *tmp = art;
    int i;
    for (i = 0; tmp != NULL; i++)
        tmp = tmp->seg;
    return i;
}

BinTree *listaTotalAnos(LL *art) {
    LL *tmp = art;
    BinTree *arvore = NULL, *bTmp = NULL;
    int ano;

    while (tmp != NULL) {
        ano = tmp->elem->ano;

        if (arvore != NULL) {

            if (arvore->stats->ano > ano)
                arvore->esq = insereBT(ano, &(arvore->esq));
                //arvore->dir=inserir(arvore->esq,ano);
                //arvore->esq = insereBT2(arvore, arvore->esq, ano);
            else
                arvore->dir = insereBT(ano, &(arvore->dir));
            //arvore->dir=inserir(arvore->dir,ano);
            // arvore->dir = insereBT2(arvore, arvore->dir, ano);
        } else {
            bTmp = (BinTree*) malloc(sizeof (BinTree));
            bTmp->stats = (Stats *) malloc(sizeof (Stats));
            bTmp->stats->ano = ano;
            bTmp->stats->nArtigos = 0;
            bTmp->stats->nAutores = 0;
            bTmp->dir = NULL;
            bTmp->esq = NULL;
            arvore = bTmp;
        }
        tmp = tmp->seg;
    }

    return arvore;
}
