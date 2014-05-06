/* 
 * File:   estruturas.h
 * Author: duarteduarte
 *
 * Created on 2 de Março de 2013, 16:38
 */

#ifndef ESTRUTURAS_H
#define	ESTRUTURAS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_INT 5
#define MAX_CHAR 1024

typedef struct artigo {
    char* inteiro;
    int numAutores;
    int ano;
    int tipoArt;
} Artigo;


typedef struct stats {
    int ano;
    int nAutores;
    int nArtigos;
} Stats;

typedef struct binTree {
    Stats *stats;
    struct binTree *esq;
    struct binTree *dir;
} BinTree;

struct binTree *raiz;


#define CONFE 0
#define REVI 1


  

#ifdef	__cplusplus
}
#endif

#endif	/* ESTRUTURAS_H */

