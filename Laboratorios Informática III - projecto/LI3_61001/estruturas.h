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
//#define MAX_listas 100

typedef struct revista {
    char inteiro[MAX_INT];
    char lista_autores[MAX_CHAR];
    char titulo[MAX_CHAR];
    char nome_revista[MAX_CHAR];
    char sigla[MAX_CHAR];
    int volume_revista;
    int num_revista;
    int pag_ini;
    int pag_fin;
    int ano;
} REV;

typedef struct conferencia {
    char inteiro[MAX_INT];
    char lista_autores[MAX_CHAR];
    char titulo[MAX_CHAR];
    char nome_conferencia[MAX_CHAR];
    int ano;
    int pag_ini;
    int pag_fin;
} CONF;

#define CONFE 0
#define REVI 1

typedef union sArtigo {
    REV revistas;
    CONF conferencias;    
} Artigo;
  

#ifdef	__cplusplus
}
#endif

#endif	/* ESTRUTURAS_H */

