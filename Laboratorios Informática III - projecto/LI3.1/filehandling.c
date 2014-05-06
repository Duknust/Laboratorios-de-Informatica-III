#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "filehandling.h"
#include "mod_ListasLigadas.h"
#include "funcoes_processamento.h"
#include "util.h"

int readJ(char *filename, int* revRej) {
    size_t len = 0;
    FILE * f = NULL;
    //char * tmp = NULL;
    char * line = NULL, *tmpLine = NULL;
    int i = 0, res = 0, rejeitados = 0;
    Artigo *tmpArt;

    f = fopen(filename, "r");
    if (f != NULL) {
        do {
            //line = fgetln(f, &len);
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL && line[0] != '-' && line[1] != '-' && line != "") {
                len = strlen(line);
                if (len > 0) {
                    tmpLine = (char *) malloc(len);
                    strncpy(tmpLine, line, len);
                }
                tmpArt = (Artigo*) malloc(sizeof (Artigo));
                res = retira_dados_REV(tmpLine, tmpArt);
                i++;
                if (res == 0)
                    insere(tmpArt, REVI);
                else rejeitados++;

            }

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }
    logRejected(filename, rejeitados);
    *revRej += rejeitados;

    return i;
}

int readC(char *filename, int* confRej) {
    size_t len = 0;
    FILE * f = NULL;
    //char * tmp = NULL;
    char * line = NULL, *tmpLine = NULL;
    int i = 0, res = 0, rejeitados = 0;
    Artigo *tmpArt;

    f = fopen(filename, "r");
    if (f != NULL) {
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL && line[0] != '-' && line[1] != '-' && line != "") {
                len = strlen(line);
                if (len > 0) {
                    tmpLine = (char *) malloc(len);
                    strncpy(tmpLine, line, len);
                }
                tmpArt = (Artigo*) malloc(sizeof (Artigo));
                res = retira_dados_CONF(tmpLine, tmpArt);
                i++;
                if (res == 0)
                    insere(tmpArt, CONFE);
                else {
                    rejeitados++;
                  //  free(tmpArt);
                  //  tmpArt=NULL;
                }
            }

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }
    logRejected(filename, rejeitados);
    *confRej += rejeitados;

    return i;
}

/*int readC(char *filename) {
    size_t len;
    FILE *f;
    char * line;
    char * res = NULL;
    int i = 0;
    Artigo *tmpArt;

    f = fopen(filename, "r");
    if (f != NULL) {
        line = fgetln(f, &len);
        do {
            line = fgetln(f, &len);
            if (line != NULL) {
                tmpArt = (Artigo*) malloc(sizeof (Artigo));
                retira_dados_CONF(line, &tmpArt->conferencias);
                i++;
                if(tmpArt->conferencias.pag_fin-tmpArt->conferencias.pag_ini>=min_pag)
                    insere(tmpArt, CONFE);
            }
        } while (line != NULL && line != "");
        fclose(f);
    }
    return i;
}*/

int read_list(char *basepath, const char *filename, int *confLidas, int *revsLidas, int* confsRej, int* revsRej) {
    size_t len = 0;
    FILE *f = NULL;
    char * line = NULL;
    char * tmp = NULL;
    *confLidas = 0;
    *revsLidas = 0;
    *confsRej = 0;
    *revsRej = 0;
    //int minPag = 0;

    char *absolute = NULL;
    absolute = (char *) malloc(sizeof (char) *(strlen(basepath) + strlen(filename)));
    strcat(absolute, basepath);
    strcat(absolute, filename);

    f = fopen(absolute, "r");

    if (f != NULL) {
        line = (char *) calloc(MAX_CHAR, sizeof (char));
        line = fgets(line, MAX_CHAR, f);
        /*tmp=(char*)malloc(len);
        strncpy(tmp, line, len-1);
         */
        min_pag = atoi(line);
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL) {
                len = strlen(line);
                if (line[len - 1] == '\n')
                    line[len - 1] = '\0';
                absolute = (char *) malloc(sizeof (char) *(strlen(basepath) + len));
                clear_str(absolute, strlen(basepath) + len);
                strcat(absolute, basepath);
                strcat(absolute, line);

                if (line[0] == 'c')
                    *confLidas += readC(absolute, confsRej);
                if (line[0] == 'j')
                    *revsLidas += readJ(absolute, revsRej);
                if (absolute != NULL) {
                    free(absolute);
                    absolute = NULL;
                }
            }

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }

    if (absolute != NULL) {
        free(absolute);
        absolute = NULL;
    }

    return (*confLidas)+(*revsLidas);
}

void logRejected(const char *filename, int nRejected) {
    /*
     * FILE *f = fopen("/Users/duarteduarte/Downloads/LI3-4TST-v2/teste1/E.txt", "w+");
    fprintf(f, "");
    fflush(f);
     */
    char path[200]; 
    sprintf(&path, "%s/%s",CAMINHO,"E.txt");
    FILE *f = fopen(path, "a");
    if (f != NULL) {
        fprintf(f, "%s\t%d\n", filename, nRejected);
        fflush(f);
        fclose(f);
    }
}

void logStats(int confsLidas, int revsLidas, int confsRej, int revsRej) {
    char path[200]; 
    sprintf(&path, "%s/%s",CAMINHO,"D.txt");
    
    FILE *f = fopen(path, "w");
    if (f != NULL) {
        fprintf(f, "Estatistica basica\n------------------\n");
        fprintf(f, "%d entradas\n", (confsLidas + revsLidas));
        fprintf(f, "%d rejeitadas\n", (confsRej + revsRej));
        fprintf(f, "%d artigos\n", (confsLidas - confsRej + revsLidas - revsRej));
        fprintf(f, "\t%d em revista\n", revsLidas - revsRej);
        fprintf(f, "\t%d em conferencias\n", confsLidas - confsRej);
        fflush(f);
        fclose(f);
    }
}