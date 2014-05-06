#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#include "hashing.h"
#include "util.h"

typedef struct autor {
    char* nome;
    int artigosComum;
    struct autor *seg;
} Autor;

typedef struct hashTableEntry {
    char* nome;
    char* key;
    Autor *coautores;
    int maxComum;
    struct hashTableEntry *seg;
} HashTE;

typedef HashTE *HashTable[CAP];

HashTable ht = {};

int hash(char* key, int keyLen) {
    unsigned int h = 0;
    int i = 0;
    for (i = 0; i < keyLen; i++)
        h += (key[i]) * (i + 1);

    return abs(h);
}

void initHT() {
    int i = 0;
    for (i = 0; i < CAP; i++)
        ht[i] = NULL;
}

void insereAutorHt(char* key, char* nome) {
    int hashcode, pos;
    HashTE *tmp = NULL;

    pos = hash(key, strlen(key)) % CAP;

    tmp = (HashTE*) malloc(sizeof (HashTE));
    tmp->key = (char*) calloc(strlen(key) + 1, sizeof (char));
    strlcpy(tmp->key, key, strlen(key) + 1);
    tmp->nome = (char*) calloc(strlen(nome) + 1, sizeof (char));
    strlcpy(tmp->nome, nome, strlen(key) + 1);
    tmp->seg = NULL;
    tmp->maxComum = 0;

    if (ht[pos] == NULL)
        ht[pos] = tmp;
    else {
        if (strcmp(ht[pos]->key, key) != 0) {
            tmp->seg = ht[pos];
            ht[pos] = tmp;
        }
    }
}

HashTE *get(char *key) {
    HashTE *tmp = ht[(hash(key, strlen(key))) % CAP];
    while (tmp != NULL && strcmp(tmp->key, key) != 0)
        tmp = tmp->seg;

    return tmp;
}

int addCoAutor(char *autor, char *coautor) {
    Autor *aux = NULL, *tmpAutor = NULL;
    int inserido = 0;
    HashTE *tmp = get(autor);

    if (tmp != NULL) {
        //insereAutorHt(autor, autor);
        //tmp = get(autor);

        aux = (Autor*) malloc(sizeof (Autor));
        aux->nome = (char*) calloc(strlen(coautor) + 1, sizeof (char));
        strlcpy(aux->nome, coautor, strlen(coautor) + 1);
        aux->artigosComum = 1;
        aux->seg = NULL;

        tmpAutor = tmp->coautores;

        if (tmpAutor == NULL) {
            tmp->coautores = aux;
            inserido = 1;
        } else {
            while (tmpAutor && !inserido) {
                if (strcmp(tmpAutor->nome, coautor) == 0) {
                    tmpAutor->artigosComum++;
                    if (tmpAutor->artigosComum > tmp->maxComum)
                        tmp->maxComum = tmpAutor->artigosComum;
                    inserido = 1;
                    free(aux);
                } else if (tmpAutor->seg == NULL) {
                    tmpAutor->seg = aux;
                    inserido = 1;
                    if (aux->artigosComum > tmp->maxComum)
                        tmp->maxComum = tmpAutor->artigosComum;
                } else
                    tmpAutor = tmpAutor->seg;
            }
        }
    }

    return !inserido;
}
//Dado um nome de autor (existente) determinar com quantos outros este escreveu artigos;

int q1qntsAutoresEscreveu(char* autor) {
    HashTE *tmp = NULL;
    Autor *aux = NULL;
    int cont = 0;

    tmp = get(autor);
    if (tmp != NULL) {
        aux = tmp->coautores;

        while (aux) {
            cont++;
            aux = aux->seg;
        }
    }

    printf("%s escreveu com %d autores\n", autor, cont);

    return cont;
}

int q2qntsArtigosComum(char* autor, char* coautor) {
    HashTE *tmp = NULL;
    Autor *aux = NULL;
    int res = 0, encontrado = 0;

    tmp = get(autor);
    if (tmp != NULL) {
        aux = tmp->coautores;

        while (aux && !encontrado) {
            if (strcmp(aux->nome, coautor) == 0) {
                res = aux->artigosComum;
                encontrado = 1;
            }
            aux = aux->seg;
        }
    }
    printf("%s e %s escreveram juntos em %d artigos\n", autor, coautor, res);
    return res;
}

void q3maxArtigosComum() {
    HashTE *tmp = NULL;
    Autor *aux = NULL;
    //int maxArtigos = 0;
    int i = 0, tmpMaxComum = 0;

    for (i = 0; i < CAP; i++)
        if (ht[i] != NULL)
            if (ht[i]->maxComum > tmpMaxComum)
                tmpMaxComum = ht[i]->maxComum;

    printf("----- Maior numero de artigos -----\n");

    for (i = 0; i < CAP; i++) {
        tmp = ht[i];
        while (tmp != NULL) {
            aux = ht[i]->coautores;
            while (aux != NULL) {

                if (aux->artigosComum == tmpMaxComum)
                    printf("%s - %s com %d artigos em comum\n", ht[i]->nome, aux->nome, tmpMaxComum);

                aux = aux->seg;
            }
            tmp = tmp->seg;
        }
    }

    /* for (i = 0; i < CAP; i++) {
         if (ht[i] != NULL) {
             tmp = ht[i];
             while (tmp) {
                 aux = tmp->coautores;
                 while (aux) {
                     if (aux->artigosComum == tmp->maxComum && aux->artigosComum > tmpMaxComum) {
                         tmpMaxComum = aux->artigosComum;
                     }
                     aux = aux->seg;
                 }
                 tmp = tmp->seg;
             }
         }

     }
     for (i = 0; i < CAP; i++) {
         if (ht[i] != NULL) {
             tmp = ht[i];
             while (tmp) {
                 aux = tmp->coautores;
                 while (aux) {
                     if (aux->artigosComum == tmpMaxComum) {
                         printf("%s - %s com %d artigos",tmp->nome,aux->nome,tmpMaxComum);
                     }
                     aux = aux->seg;
                 }
                 tmp = tmp->seg;
             }
         }
     }*/
    //printf("%s - %s com %d artigos", maxNome[0], maxNome[1], *maxArtigos);

}

int qntsHT() {
    int res = 0, i = 0;
    HashTE *tmp = NULL;
    
    for (i = 0; i < CAP; i++) {
        tmp = ht[i];
        while (tmp != NULL) {
            res++;
            tmp = tmp->seg;
        }
    }

    return res;
}

void q4Top10Artigos() {
    HashTE *tmp = NULL;
    int lstQnt[10] = {};
    char* lstNomes[10] = {};
    char* tmpNome = NULL;
    int res = 0, inserido = 0;
    int valormin = 0, posmin = 0;
    int primDez = 0;
    int i = 0;
    /*
        while (i < 10) {
            while (i < 10 && ht) {
                while (i < 10 && ht.coautores) {
                    lstQnt[i] = ht.coautores->artigosComum;
                    lstNomes[i] = ht.coautores->nome;
                    ht.coautores = ht.coautores->seg;
                    i++;
                }
                ht = ht.seg;
            }
     */

    while (tmp) {
        res = 0;
        while (tmp->coautores) {
            res += tmp->coautores->artigosComum;
            tmp->coautores = tmp->coautores->seg;
        }
        if (primDez < 10) {
            lstNomes[primDez] = tmp->nome;
            lstQnt[primDez] = res;
            // PRENCHER AS 10 POSIÇOES
            // GUARDAR O MINIMO E A SUA POS!
        } else if (res > valormin) {
            posmin = calcularPosMin(lstQnt, 10);
            lstQnt[posmin] = res;
            lstNomes[posmin] = tmp->nome;
        }
        tmp = tmp->seg;
    }

    printf("-----TOP10-----\n\n");
    for (res = 0; res < 10; res++) {

        printf("%d > &s &d", res, lstNomes[res], lstQnt[res]);
    }
}

int calcularPosMin(int listaNomes[], int tamanho) {
    int i = 0;
    int posmin = 0;
    int valor = listaNomes[0];

    for (i = 1; i < tamanho; i++)
        if (listaNomes[i] < valor) {

            valor = listaNomes[i];
            posmin = i;
        }

    return posmin;
}

int processaAutores(const char *str) {
    char *tokens[100] = {}, *ch, *sep = ",";
    char *tmp1, *tmp2, *aux;
    int initPos = 0, nextPos = 0, i = 0, contador = 0, j = 0;

    tmp1 = str;
    tmp2 = str;

    while ((*tmp1) != '\0') {
        tmp2 = tmp1;
        initPos = 0;
        nextPos = initPos;
        while ((*tmp2) != ',' && (*tmp2) != '\0') {
            tmp2++;
            nextPos++;
        }
        contador++;
        tokens[i] = (char *) calloc(nextPos - initPos + 2, sizeof (char));
        strncpy(tokens[i], tmp1, nextPos - initPos);
        tokens[i][nextPos - initPos] = '\0';
        i++;

        tmp1 = (*tmp2 != '\0') ? tmp2 + 1 : tmp2;
    }

    for (i = 0; i < contador; i++) {
        aux = trim(tokens[i]);
        strncpy(tokens[i], trim(tokens[i]), strlen(tokens[i]));
    }

    for (i = 0; i < contador; i++) {
        insereAutorHt(tokens[i], tokens[i]);
        for (j = 0; j < contador; j++) {
            if (j != i)
                addCoAutor(tokens[i], tokens[j]);
        }
    }

    return 0;
}