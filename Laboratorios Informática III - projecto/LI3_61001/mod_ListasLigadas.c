
#include <string.h>

#include "mod_ListasLigadas.h"
#include "estruturas.h"

int insere(Artigo *art, int tipo) {
    LLptr tmp;

    tmp = (LL*) malloc(sizeof (LL));
    tmp->tipo = tipo;
    tmp->elem = art;
    tmp->seg = artigos;
    tmp->ant = NULL;

    if (artigos != NULL)
        artigos->ant = tmp;
    artigos = tmp;
    

    return 0;
}



int remover(Artigo *art) {
    LLptr tmp;
    int flag=0;
    if (art == NULL)
        return -1;
    
    tmp = artigos;

    do {
        if ((tmp->tipo==CONFE) && 
                (tmp->elem != NULL) &&
                (art->conferencias.inteiro == tmp->elem->conferencias.inteiro)) {
            if (tmp->ant != NULL)
                tmp->ant->seg = tmp->seg;
            if (tmp->seg != NULL)
                tmp->seg->ant = tmp->ant;
            flag=1;
            tmp=NULL;
        }
        else
            tmp = tmp->seg;
    } while (tmp != NULL && flag==0);

    free (tmp);
}

void imprimeElems(){
    LLptr tmp = artigos;
    
    
    while (tmp){
        printf("%s\n",tmp->elem->conferencias.inteiro);
        printf("%s\n",tmp->elem->revistas.inteiro);
        tmp=tmp->seg;
    }
}


int comprimento(LLptr lst){
    LLptr copia=NULL;
    int cnt=0;
    for(copia=lst; copia==NULL; copia=copia->seg)
        cnt++;
    
    return cnt;
}