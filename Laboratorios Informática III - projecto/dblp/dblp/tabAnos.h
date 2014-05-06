/* 
 * File:   tabAnos.h
 * Author: duarteduarte
 *
 * Created on 10 de Abril de 2013, 23:10
 */

#ifndef TABANOS_H
#define	TABANOS_H

#define BASEYEAR 1900
#define MAX_ANOS 114

#ifdef	__cplusplus
extern "C" {
#endif
    
    void *initTA();
    void *insertTA(TabAutores *tabA, int ano, int nautores);
    int intervalosAnos(int anoInicial, int anoFinal); // COMENTAR
    int nAutoresArtigo(); // COMENTAR
    int anoAutoresArtigo(); // COMENTAR
    int criaG();


#ifdef	__cplusplus
}
#endif

#endif	/* TABANOS_H */

