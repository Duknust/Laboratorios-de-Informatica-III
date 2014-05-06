#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "filehandling.h"
#include "funcoes_processamento.h"
#include "util.h"
#include "tabAnos.h"


FILE *g = NULL;

int gestorFilehandling(char *basepath, const char *filename) {
    int res = 0;
    initHT();
    read_list(basepath, filename);
    res = criaG();
    return res;
}

int readJ(char *filename, int* revRej) {
    size_t len = 0;
    FILE * f = NULL;
    char * line = NULL, *tmpLine = NULL;
    int i = 0, res = 0, rejeitados = 0;
    Artigo *tmpArt = NULL;

    f = fopen(filename, "r");
    if (f != NULL) {
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL && line[0] != '-' && line[1] != '-' && line != "") {
                len = strlen(line);
                if (len > 0) {
                    tmpLine = (char *) malloc(len);
                    strlcpy(tmpLine, line, len);
                }

                tmpArt = retira_dados_REV(tmpLine, len);
                i++;
                if (tmpArt != NULL)
                    insertTA(tabelaAutores, tmpArt->ano, tmpArt->numAutores);
                else
                    rejeitados++;

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
    char * line = NULL, *tmpLine = NULL;
    int i = 0, res = 0, rejeitados = 0;
    Artigo *tmpArt = NULL;

    f = fopen(filename, "r");
    if (f != NULL) {
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL && line[0] != '-' && line[1] != '-' && line != "") {
                len = strlen(line);
                if (len > 0) {
                    tmpLine = (char *) malloc(len);
                    strlcpy(tmpLine, line, len);
                }

                tmpArt = retira_dados_CONF(tmpLine, len);
                i++;
                if (tmpArt != NULL)
                    insertTA(tabelaAutores, tmpArt->ano, tmpArt->numAutores);
                else {
                    rejeitados++;
                }
            }

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }
    logRejected(filename, rejeitados);
    *confRej += rejeitados;

    return i;
}

int read_list(char *basepath, const char *filename) {
    size_t len = 0;
    FILE *f = NULL;
    char * line = NULL;

    int confLidas, revsLidas, confsRej, revsRej;
    confLidas = 0;
    revsLidas = 0;
    confsRej = 0;
    revsRej = 0;
    int naut = 0;

    char *absolute = NULL;
    absolute = (char *) malloc(sizeof (char) *(strlen(basepath) + strlen(filename)));
    strcat(absolute, basepath);
    strcat(absolute, filename);

    initTA();

    f = fopen(absolute, "r");

    if (f != NULL) {
        line = (char *) calloc(MAX_CHAR, sizeof (char));
        line = fgets(line, MAX_CHAR, f);

        min_pag = atoi(line);
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL) {
                len = strlen(line);
                if (line[len - 1] == '\n')
                    line[len - 1] = '\0';
                absolute = (char *) malloc(sizeof (char) * (strlen(basepath) + len));
                clear_str(absolute, strlen(basepath) + len);
                strcat(absolute, basepath);
                strcat(absolute, line);

                if (line[0] == 'c')
                    confLidas += readC(absolute, &confsRej);
                if (line[0] == 'j')
                    revsLidas += readJ(absolute, &revsRej);
            }

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }

    if (absolute != NULL) {
        free(absolute);
        absolute = NULL;
    }
    free(line);

    logStats(confLidas, revsLidas, confsRej, revsRej);

    return 0;
}

void logRejected(const char *filename, int nRejected) {
    char path[200];
    sprintf(path, "%s%s", CAMINHO, "E.txt");
    FILE *f = fopen(path, "a");
    if (f != NULL) {
        fprintf(f, "%s\t%d\n", filename, nRejected);
        fflush(f);
        fclose(f);
    }
}

void logStats(int confsLidas, int revsLidas, int confsRej, int revsRej) {
    char path[200];
    sprintf(path, "%s%s", CAMINHO, "D.txt");

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

int readIntervalos(char* fileName) {
    size_t len = 0;
    FILE *f = NULL;
    char * line = NULL, tmp[4];
    int i = 0, anoInicial = 0, anoFinal = 0, res = 0;
    int j;

    char *absolute = NULL;
    absolute = (char *) calloc((strlen(CAMINHO) + strlen(fileName)), sizeof (char));
    clear_str(absolute, strlen(CAMINHO) + strlen(fileName));

    strcat(absolute, CAMINHO);
    strcat(absolute, fileName);

    logIntervaloTIT();

    f = fopen(absolute, "r");

    if (f != NULL) {
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL) {
                len = strlen(line);
                if (line[len - 1] == '\n')
                    line[len - 1] = '\0';

                for (i = 0; line[i] != '-'; i++)
                    tmp[i] = line[i];

                anoInicial = atoi(tmp);
                i++;
                for (; line[i] != '\0'; i++)
                    tmp[i - 5] = line[i];
                anoFinal = atoi(tmp);
            }

            res = intervalosAnos(anoInicial, anoFinal);

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }

    if (absolute != NULL) {
        free(absolute);
        absolute = NULL;
    }
    free(line);

    return res;
}

int readAno(char* fileName) {
    size_t len = 0;
    FILE *f = NULL;
    char * line = NULL, tmp[4];
    int i = 0, ano = 0, res = 0;

    char *absolute = NULL;
    absolute = (char *) calloc((strlen(CAMINHO) + strlen(fileName)), sizeof (char));
    clear_str(absolute, strlen(CAMINHO) + strlen(fileName));

    strcat(absolute, CAMINHO);
    strcat(absolute, fileName);

    logAnosAutoresPercentagemTIT();

    f = fopen(absolute, "r");

    if (f != NULL) {
        do {
            line = (char *) calloc(MAX_CHAR, sizeof (char));
            line = fgets(line, MAX_CHAR, f);

            if (line != NULL) {
                len = strlen(line);
                if (line[len - 1] == '\n')
                    line[len - 1] = '\0';

                for (i = 0; line[i] != '\0'; i++)
                    tmp[i] = line[i];

                ano = atoi(tmp);
                i++;
            }

            res = anosAutoresPercentagem(ano);

        } while (line != NULL && line != "" && !feof(f));
        fclose(f);
    }

    if (absolute != NULL) {
        free(absolute);
        absolute = NULL;
    }
    free(line);

    return res;
}

void logIntervalo(int anoInicial, int anoFinal, int nArtigos) {
    if (g != NULL) {
        fprintf(g, "\"%d-%d\",\"%d\"\n", anoInicial, anoFinal, nArtigos);
        printf("%d-%d, %d\n", anoInicial, anoFinal, nArtigos);

    }
}

void logAutoresArtigo(int nAutores, int nArtigos) {
    if (g != NULL) {
        fprintf(g, "\"%d\",\"%d\"\n", nAutores, nArtigos);
        printf("%d, %d\n", nAutores, nArtigos);
    }
}

void logAnAutArt(int ano, int nAutores, int nArtigos) {
    if (g != NULL) {
        fprintf(g, "\"%d\",\"%d\",\"%d\"\n", ano, nAutores, nArtigos);
        printf("%d, %d, %d\n", ano, nAutores, nArtigos);
    }
}

void logAnosAutoresPercentagem(int ano, int nAutores, double percentagem) {
    if (g != NULL) {
        fprintf(g, "\"%d\",\"%d\",\"%.2f\"\n", ano, nAutores, percentagem);
        printf("%d, %d, %.2f\n", ano, nAutores, percentagem);
    }
}

int initG() {
    char path[200];
    int res = 0;
    sprintf(path, "%s/%s", CAMINHO, "G.csv");

    g = fopen(path, "a");
    if (g == NULL) {
        res = -1;
    }

    return res;
}

void closeG() {
    if (g != NULL) {
        fflush(g);
        fclose(g);
    }
}

void logAnAutArtTIT() {
    if (g != NULL)
        fprintf(g, "\"ano\",\"#autores\",\"#artigos\"\n");
    printf("ano, #autores, #artigos\n");
}

void logIntervaloTIT() {
    if (g != NULL)
        fprintf(g, "\"intervalo\",\"#artigos\"\n");
    printf("intervalo, #artigos\n");
}

void logAutoresArtigoTIT() {
    if (g != NULL)
        fprintf(g, "\"#autores\",\"#artigos\"\n");
    printf("#autores, #artigos\n");
}

void logAnosAutoresPercentagemTIT() {
    if (g != NULL)
        fprintf(g, "\"ano\",\"#autores\",\"percentagem\"\n");
    printf("ano, #autores, percentagem\n");
}

int criaG(char *fileName) {

    initG();

    logAnAutArtTIT();
    anoAutoresArtigo();
    logAutoresArtigoTIT();
    nAutoresArtigo();
    readIntervalos("datas3.txt");
    // logIntervaloTIT(); // AQUI EM VEZ DISTO TEM DE CHAMAR A QUE LE O TXT
    // intervalosAnos(anoInicial, anoFinal); // CORRIGIR
    //logAnosAutoresPercentagemTIT(); //AQUI EM VEZ DISTO TEM DE CHAMAR A QUE LE O TXT
    readAno("datas4.txt");

    closeG();

    return 0;
}