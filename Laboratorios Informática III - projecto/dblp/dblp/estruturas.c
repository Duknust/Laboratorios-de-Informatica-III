#include <stdio.h>
#include <stdlib.h>

#include "estruturas.h"

/*BinTree *insereBT(int ano, BinTree *arvore) {

    if (arvore != NULL) {
        if (arvore->stats->ano > ano) {
            arvore->esq = insereBT(ano, (arvore->esq));
        } else
            arvore->dir = insereBT(ano, (arvore->dir));
    } else {
        arvore = (BinTree*) malloc(sizeof (BinTree));
        arvore->stats = (Stats *) malloc(sizeof (Stats));
        arvore->stats->ano = ano;
        arvore->stats->nArtigos = 0;
        arvore->stats->nAutores = 0;
        arvore->dir = NULL;
        arvore->esq = NULL;
    }

    return arvore;
}*/



    
/*
BinTree *insereBT2(BinTree *raiz, BinTree *arvore, int ano) {
    if (!arvore) {
        arvore = (BinTree*) malloc(sizeof(BinTree)); //disponibiliza memoria para a arvore 
        if (!arvore) {
            printf("Falta de memoria");
            exit(0);
        }
        arvore->esq = NULL;
        arvore->dir = NULL;
        arvore->stats->ano = ano;
        if (!raiz) return arvore; //primeira entrada 
        if (ano < raiz->stats->ano) raiz->esq = arvore;
        else raiz->dir = arvore;
        return arvore;
    }
    if (ano < arvore->stats->ano) insereBT2(arvore, arvore->esq, ano);
    else
        insereBT2(arvore, arvore->dir, ano);

}
 */

/*        
        struct arvore *sarvore(struct arvore *raiz,struct arvore *r, char info) 
{ 
if(!r){ 
r=(struct arvore*)malloc(sizeof(struct arvore));//disponibiliza memoria para a arvore 
      if(!r) { 
      printf("Falta de memoria"); 
      exit(0); 
      } 
      r->esquerda=NULL; 
      r->direita=NULL; 
      r->info=info; 
      if (!raiz)return r;//primeira entrada 
      if(info<raiz->info) raiz->esquerda=r; 
      else raiz->direita=r; 
      return r; 
      } 
   if (info<r->info) sarvore(r,r->esquerda,info); 
  else 
sarvore(r,r->direita,info); 
}*/
/*
void inserir(BinTree *pRaiz, int numero) {
    if (pRaiz == NULL) {
        pRaiz = (BinTree*) malloc(sizeof(BinTree));
        pRaiz->esq = NULL;
        pRaiz->dir = NULL;
        pRaiz->stats->ano = numero;
    } else {
        if (numero < pRaiz->stats->ano)
            inserir(&(pRaiz->esq), numero);
        else
            inserir(&(pRaiz->dir), numero);
    }
}*/