/* 
 * File:   filehandling.h
 * Author: duarteduarte
 *
 * Created on 23 de Fevereiro de 2013, 16:25
 */

#ifndef FILEHANDLING_H
#define	FILEHANDLING_H

#ifdef	__cplusplus
extern "C" {
#endif

    int readJ(char *fileName, int* revRej);
    int readC(char *filename, int* confRej);
    int read_list(char * basepath, const char *filename, int * confLidas, int * revsLidas, int* confsRej, int* revsRej);
    void logRejected(const char *filename, int nRejected);
    void logStats(int confsAceites, int revsAceites, int confsRej, int revsRej);


#ifdef	__cplusplus
}
#endif

#endif	/* FILEHANDLING_H */

