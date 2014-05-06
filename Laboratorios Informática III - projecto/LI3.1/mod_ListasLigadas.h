/* 
 * File:   mod_ListasLigadas.h
 * Author: duarteduarte
 *
 * Created on 20 de Fevereiro de 2013, 20:28
 */

#ifndef MOD_LISTASLIGADAS_H
#define	MOD_LISTASLIGADAS_H

#include "estruturas.h"


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct ll {
        int tipo;
        Artigo *elem;
        int nElems;
        struct ll *seg;
        struct ll *ant;
    } LL, *LLptr;

    LLptr returnArtigos();
#ifdef	__cplusplus
}
#endif

#endif	/* MOD_LISTASLIGADAS_H */

