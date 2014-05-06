#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#include "hashing.h"
#include "util.h"
#include "estruturas.h"

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
        if (!existsKey(ht[pos], key)) {
            tmp->seg = ht[pos];
            ht[pos] = tmp;
        }
    }
}

int existsKey(HashTE *value, char *key) {
    HashTE *tmp = value;
    int res = 0;

    while (tmp != NULL && !res) {
        if (strcmp(tmp->key, key) == 0)
            res = 1;
        tmp = tmp->seg;
    }

    return res;
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

    for (i = 0; i < CAP; i++) {
        tmp = ht[i];
        while (tmp != NULL) {
            if (tmp->maxComum > tmpMaxComum)
                tmpMaxComum = tmp->maxComum;
            tmp = tmp->seg;
        }
    }
    printf("----- Maior numero de artigos -----\n");

    for (i = 0; i < CAP; i++) {
        tmp = ht[i];
        while (tmp != NULL) {
            aux = tmp->coautores;
            while (aux != NULL) {
                if (aux->artigosComum == tmpMaxComum)
                    printf("%s - %s com %d artigos em comum\n", tmp->nome, aux->nome, tmpMaxComum);

                aux = aux->seg;
            }
            tmp = tmp->seg;
        }
    }
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

int lenCoAutores(Autor* coautores) {
    Autor *tmp = coautores;
    int res = 0;
    while (tmp != NULL) {
        res++;
        tmp = tmp->seg;
    }
    return res;
}

int recalcMin(Top10Entry *top10, int *posmin, int howManyPos) {
    int i = 0, min = 0;
    if (top10 != NULL) {
        min = top10[0].nCoautores;
        *posmin = 0;
        for (i = 1; i < howManyPos; i++) {
            if (top10[i].nCoautores > 0 && top10[i].nCoautores < min) {
                min = top10[i].nCoautores;
                *posmin = i;
            }
        }
    }
    return min;
}

void initTop10(Top10Entry *top10) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        top10[i].nCoautores = -1;
    }
}

void insereTop10(Top10Entry *top10, int nCoautores, char* nome, int posmin, int min) {
    int i = 0, inserido = 0;
    for (i = 0; i < 10; i++) {
        if (top10[i].nCoautores == -1) {
            top10[i].nCoautores = nCoautores;
            top10[i].nome = nome;
            inserido = 1;
        }
    }
    if (!inserido) {
        if (nCoautores > min) {
            top10[posmin].nCoautores = nCoautores;
            top10[posmin].nome = nome;
        } else if (nCoautores == min) {
            if (strcmp(nome, top10[posmin].nome) < 0) {
                top10[posmin].nome = nome;
            }

        }
    }
}

void mySort(Top10Entry *top10) {
    Top10Entry tmp;
    int posmin=0, i,j, min;
    
    for(i=0;i<10;i++){
        min = recalcMin(top10+i,&posmin,10-i);
        tmp.nCoautores=top10[i].nCoautores;
        tmp.nome=top10[i].nome;
        
        top10[i].nCoautores = top10[posmin+i].nCoautores;
        top10[i].nome = top10[posmin+i].nome;
        
        top10[posmin+i].nCoautores=tmp.nCoautores;
        top10[posmin+i].nome=tmp.nome;
    }
}

void sort(Top10Entry *top10){
    Top10Entry tmp;
    int posmin=-1, i, j, count=10;
     //tmp.nCoautores=top10[i].nCoautores;
      //  tmp.nome=top10[i].nome;
        
        //top10[recalcMin(&top10,&posmin)].nCoautores=
    while(count){
    for (i=0;i<10;i++)
        for (j=1;j<10;j++)
            if(top10[j].nCoautores<top10[i].nCoautores){
                tmp.nCoautores=top10[j].nCoautores;
                tmp.nome=top10[j].nome;
                
                top10[j].nCoautores=top10[i].nCoautores;
                top10[j].nome=top10[i].nome;
                
                top10[i].nCoautores=tmp.nCoautores;
                top10[i].nome=tmp.nome;
            }
    count--;
    }
}

void reverseTOP10(Top10Entry *top10){
    Top10Entry tmp;
    int i=0;
    for (i=0;i<5;i++){
        tmp.nCoautores=top10[i].nCoautores;
        tmp.nome=top10[i].nome;
        
        top10[i].nCoautores=top10[9-i].nCoautores;
        top10[i].nome=top10[9-i].nome;
        
        top10[9-i].nCoautores=tmp.nCoautores;
        top10[9-i].nome=tmp.nome;
    }
        
}

void q4Top10Artigos() {
    HashTE *tmp = NULL;
    Top10Entry top10[10] = {};
    initTop10(&top10);
    int i = 0, len = 0, posmin = 0, min = 0;

    for (i = 0; i < CAP; i++) {
        tmp = ht[i];
        while (tmp) {
            len = lenCoAutores(tmp);
            insereTop10(&top10,len,tmp->nome,posmin, min);
            min = recalcMin(&top10, &posmin,10);
            tmp = tmp->seg;
        }
    }
    mySort(&top10);
    reverseTOP10(&top10);
    printf("-----TOP10-----\n");
    for (i = 0; i < 10; i++) {
        printf("%d > %s %d\n", i+1, top10[i].nome, top10[i].nCoautores-1); // Há uma diferença de um coautor em todas as entradas por isso subtrai uma unidade.
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