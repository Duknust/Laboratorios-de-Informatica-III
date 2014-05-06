/* 
 * File:   funcoes_processamento.h
 * Author: duarteduarte
 *
 * Created on 23 de Fevereiro de 2013, 16:06
 */
#include "estruturas.h"

#ifndef FUNCOES_PROCESSAMENTO_H
#define	FUNCOES_PROCESSAMENTO_H

#ifdef	__cplusplus
extern "C" {
#endif
    //int i;
    //char dados [300];
    int min_pag;

    int retira_dados_REV(const char *dados, Artigo* art);
    int retira_dados_CONF(const char *dados, Artigo* art);
    char * strLower(const char *str);

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCOES_PROCESSAMENTO_H */

