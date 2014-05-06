/* 
 * File:   hashing.h
 * Author: duarteduarte
 *
 * Created on 23 de Abril de 2013, 22:24
 */

#ifndef HASHING_H
#define	HASHING_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CAP 2000

    int processaAutores(const char *str);
    int qntsHT();
    void q4Top10Artigos();
    void q3maxArtigosComum();
    int q2qntsArtigosComum(char* autor, char* coautor);
    int q1qntsAutoresEscreveu(char* autor);

#ifdef	__cplusplus
}
#endif

#endif	/* HASHING_H */

