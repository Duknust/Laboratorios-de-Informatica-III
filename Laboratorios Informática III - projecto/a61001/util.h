/* 
 * File:   util.h
 * Author: duarteduarte
 *
 * Created on 23 de Fevereiro de 2013, 16:12
 */

#ifndef UTIL_H
#define	UTIL_H

#include "estruturas.h"
#include "tabAnos.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    //#define CAMINHO "/Users/duarteduarte/Downloads/LI3-4TST-v2/teste2/"
    // static char *CAMINHO="/Users/duarteduarte/Downloads/LI3-4TST-v2/teste2/";
    //  static char *CAMINHO="/Users/duarteduarte/Desktop/Teste 5/";
    //static char *CAMINHO="";
    static char *CAMINHO = "";
    
    //static char *CAMINHO="/Users/duarteduarte/Downloads/teste5/";
    void clear_str(char * array, int lenght);
    void freeStatus(Status* toFree);
    char * trim(char* str);
    int numeroAutores(char* listaAut);
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

