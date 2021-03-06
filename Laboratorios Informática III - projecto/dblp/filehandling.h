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
    int readC(char *fileName, int* confRej);
    int read_list(char * basePath, const char *fileName);
    void logRejected(const char *fileName, int nRejected);
    void logStats(int confsAceites, int revsAceites, int confsRej, int revsRej);
    void logIntervalo(int anoInicial, int anoFinal, int nArtigos);
    void logAutoresArtigo(int nAutores, int nArtigos);
    void logAnAutArt(int ano, int nAutores, int nArtigos);
    void logAnosAutoresPercentagem(int ano, int nAutores, double percentagem);
    void logStatsTIT();
    void logIntervaloTIT();
    void logAutoresArtigoTIT();
    void logAnAutArtTIT();
    void logAnosAutoresPercentagemTIT();
    int readIntervalos(char *fileName);
    
    int gestorFilehandling (char *basepath, const char *filename);
//    
    int initG();
    void closeG();
    

   // static Artigo *tmpArt=NULL;
#ifdef	__cplusplus
}
#endif

#endif	/* FILEHANDLING_H */

