/* 
 * File:   mod_estatistico.h
 * Author: duarteduarte
 *
 * Created on 24 de Março de 2013, 22:18
 */

#ifndef MOD_ESTATISTICO_H
#define	MOD_ESTATISTICO_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "estruturas.h"
#include "mod_ListasLigadas.h"
    
int numeroAutores(char* listaAut);
BinTree *listaTotalAnos(LL *art);


#ifdef	__cplusplus
}
#endif

#endif	/* MOD_ESTATISTICO_H */

