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
        char* autores; 
        int numAutores;
        int ano;
    } Artigo;

    typedef struct stats {
        int ano;
        int nAutores;
        int nArtigos;
    } Stats;

    typedef struct status {
        int nAutores;
        int nArtigos;
        struct status *seg;
    } Status;

    typedef struct nAutSTA {
        int nAutSTA[114][10];
    } NautSTA;

    typedef struct nAutDIN {
        int ano;
        int nAutores;
        int nArtigos;
        struct nAutDIN *seg;
    } NautDIN;

    typedef struct tabAutores {
        NautDIN *nDin;
        NautSTA *nSta;
    } TabAutores;
    
    typedef struct top10Entry {
        int nCoautores;
        char* nome;
    }Top10Entry;


#define CONFE 0 // COMENTAR
#define REVI 1 // COMENTAR




#ifdef	__cplusplus
}
#endif

#endif	/* ESTRUTURAS_H */

