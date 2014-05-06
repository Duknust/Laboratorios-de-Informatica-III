#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes_processamento.h"
#include "util.h"
#include "estruturas.h"
#include "hashing.h"



#define MAXSTRING 2000
#define MAXINT 10
#define TMPTAM 2000  // CORRIGIR
#define TAM_BASE 512

Artigo *retira_dados_REV(const char *dados, int len) {

    int i = 0, j = 0;
    char inteiro[MAXINT] = {};
    char lista_autores [TAM_BASE] = {};
    char titulo [TAM_BASE] = {};
    char nome_revista [TAM_BASE] = {};
    char sigla[TAM_BASE] = {};
    int volume_revista;
    int num_revista;
    int pag_ini;
    int pag_fin;
    int ano;
    //int len = strlen(dados);
    char tmp[TAM_BASE] = {};
    int rejeitado = 0;
    Artigo *tmpArt = NULL;
    char path[200]; // COMENTAR blank

    //REV * rev;

    rejeitado = (rejeita_dados(dados));

    // if (rejeitado)
    //      printf("%c%c%c%c\n", dados[0], dados[1], dados[2], dados[3]);

    if (!rejeitado) {

        for (i = 0; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            inteiro[j++] = dados[i]; /*começa um a frente no proximo*/
        }
        //      printf("-------\n");
        // printf("int-> %s\n", inteiro);
        //  printf("-------\n");

        j = 0;
        for (i; i < len && dados[i] != ':' && dados[i] != '\0'; i++) {
            lista_autores[j++] = dados[i]; /*começa um a frente no proximo*/
        }
        //printf("autores-> %s\n", lista_autores);

        j = 0;
        for (++i; i < len && dados[i] != '.' && dados[i] != '\0'; i++) {
            titulo[j++] = dados[i]; /*começa um a frente no proximo*/
        }
        // printf("titulo-> %s\n", titulo);

        if (dados[i] != '\0' || dados[i] != '\n') {

            j = 0;
            for (++i; i < len && dados[i] != '(' && dados[i] != '\0'; i++) { /*neste caso tem de ficar o parentesis, como ponho?*/
                nome_revista[j++] = dados[i];
            }
            //  printf("nomeRev-> %s\n", nome_revista);

            j = 0;
            for (++i; i < len && dados[i] != ')' && dados[i] != '\0'; i++) { /*neste caso tem de ficar o parentesis, como ponho?*/
                sigla[j++] = dados[i];
            }
            //printf("sigla-> %s\n", sigla);
        }

        j = 0;
        clear_str(&tmp, TAM_BASE);
        for (i += 2; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        volume_revista = atoi(tmp);
        // printf("volume-> %d\n", volume_revista);


        j = 0;
        clear_str(&tmp, TAM_BASE);
        if (dados[i] == ' ') i++;
        if (dados[i] == '(') i++;
        for (i; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        num_revista = atoi(tmp);
        //printf("numRev-> %d\n", num_revista);

        j = 0;
        clear_str(&tmp, TAM_BASE);
        if (dados[i] == ')')i++;
        if (dados[i] == ':')i++;
        for (i; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_ini = atoi(tmp);
        //printf("PI-> %d\n", pag_ini);

        j = 0;
        clear_str(&tmp, TAM_BASE);
        if (dados[i] == ' ') i++;
        if (dados[i] == '-') i++;
        for (i; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_fin = atoi(tmp);
        //printf("PF-> %d\n", pag_fin);

        j = 0;
        clear_str(&tmp, TAM_BASE);
        while (!(isdigit(dados[i])) && i < len) i++;
        for (i; i < len && dados[i] != ')' && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        ano = atoi(tmp);
        //printf("ano-> %d\n", ano);
        //      if (titulo == ) rejeitado = 1;
        //      if (nome_revista == {})rejeitado =1;
        //if (!isalpha(trim(lista_autores))) rejeitado = 1;
        if (numeroAutores(trim(lista_autores)) == 0) rejeitado = 1;
        // if ((strcmp("", titulo) == 0) || (titulo[0] == '\0')) rejeitado = 1;
        // if ((strcmp("", nome_revista) == 0) || (nome_revista == '\0')) rejeitado = 1;
        // if ((strcmp("", sigla) == 0) || (sigla == '\0')) rejeitado = 1;
        if (volume_revista == 0) rejeitado = 1;
        if (num_revista == 0) rejeitado = 1;
        if (contemNum(sigla)) rejeitado = 1;
        if (pag_ini == 0) rejeitado = 1;
        if (pag_fin == 0) rejeitado = 1;
        if (ano == 0) rejeitado = 1;
        if (((pag_fin - pag_ini) + 1) < min_pag) rejeitado = 1;

        // if (rejeitado)
        //     printf("%s\n", inteiro);

        if (!rejeitado) {
            tmpArt = (Artigo*) malloc(sizeof (Artigo));
           // tmpArt->autores = (char*) calloc(len, sizeof (char));
            //strlcpy(tmpArt->autores, trim(lista_autores), strlen(lista_autores));
            tmpArt->numAutores = numeroAutores(trim(lista_autores));
            tmpArt->ano = ano;
            processaAutores(lista_autores);
        }
    }
   // if (rejeitado)
     //       printf("%s\n",/* nome_revista, */inteiro/*, tmpArt->numAutores*/);

    return tmpArt;
}

Artigo *retira_dados_CONF(const char *dados, int len) {

    int i, j = 0;
    char nome_conferencia [TAM_BASE] = {};
    char inteiro[MAXINT] = {};
    char lista_autores [TAM_BASE] = {};
    char titulo[TAM_BASE] = {};
    int pag_ini;
    int pag_fin;
    int ano;
    //int len = strlen(dados);
    char tmp[TAM_BASE] = {};
    int rejeitado = 0;
    Artigo *tmpArt = NULL;
    char path[200];

    rejeitado = (rejeita_dados(dados));

    // if (rejeitado)
    //     printf("%c%c%c%c\n", dados[0], dados[1], dados[2], dados[3]);

    if (!rejeitado) {
        
        for (i = 0; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            inteiro[j++] = dados[i];
        }

        //printf("------\n", inteiro);
        // printf("int-> %s\n", inteiro);
        // printf("------\n", inteiro);

        j = 0;
        for (i; i < len && dados[i] != '\0' && dados[i] != ':'; i++) {
            lista_autores[j++] = dados[i];
        }

        j = 0;
        if (i < len) i++;
        for (i; i < len && dados[i] != '\0' && dados[i] != '.'; i++) {
            titulo[j++] = dados[i];
        }
        //printf("titulo-> %s\n", titulo);
        i++;
        if (isdigit(dados[i])) rejeitado = 1;
        j = 0;
        // for (i = i + 2; dados[i] != ' '&& dados[i] != '\0'; i++) {
        if (i < len) i++;
        for (i; i < len && dados[i] != '\0' && (!isdigit(dados[i])); i++) {
            nome_conferencia[j++] = dados[i];
        }
        //     strcpy(nome_conferencia,"REJECT");
        //if (isdigit(dados[i])) printf ("NAO");
        //if (isdigit(dados[i])) printf ("%c \n",dados[i]);
        // printf("nomeConf-> %s\n", nome_conferencia);
        //trim(nome_conferencia);
        // if (isdigit(nome_conferencia[0])) rejeitado = 1; //TA AQUI A CENA DO ERRO, ESTA A PROCURAR FORA E ESTOURA!!

        j = 0;
        clear_str(&tmp, TAM_BASE);
        for (i; i < len && dados[i] != '\0' && dados[i] != ':'; i++) {
            tmp[j++] = dados[i];
        }
        if (contemLet(tmp)) rejeitado = 1;
        ano = atoi(tmp);
        //printf("ano-> %d\n", ano);

        j = 0;
        clear_str(&tmp, TAM_BASE);
        if (i < len) i++;
        for (i; i < len && dados[i] != '\0' && dados[i] != '-'; i++) {
            tmp[j++] = dados[i];
        }
        if (contemLet(tmp)) rejeitado = 1;
        pag_ini = atoi(tmp);
        //printf("PI-> %d\n", pag_ini);

        j = 0;
        clear_str(&tmp, TAM_BASE);
        if (i < len) i++;
        for (i; i < len && dados[i] != '\0' && isdigit(dados[i]); i++) {
            tmp[j++] = dados[i];
        }
        if (contemLet(tmp)) rejeitado = 1;
        pag_fin = atoi(tmp);
        //printf("PF-> %d\n", pag_fin);
        clear_str(&tmp, TAM_BASE);
        //trim(lista_autores);
        //if (!isalpha(lista_autores[0])) rejeitado = 1;        
        //  if ((strcmp("", lista_autores) == 0) || (lista_autores[0] == '\0')) rejeitado = 1;
        if (numeroAutores(trim(lista_autores)) == 0) rejeitado = 1;
        if ((strcmp("", titulo) == 0) || (titulo[0] == '\0')) rejeitado = 1;
        //  if ((strcmp("", nome_conferencia) == 0) || (nome_conferencia == '\0')) rejeitado = 1;
        if (nome_conferencia == NULL) rejeitado = 1;
        if (strcmp("", nome_conferencia) == 0) rejeitado = 1;
        // if (strcmp("REJECT",nome_conferencia)==0) rejeitado = 1;
        //if (!isalnum(trim(nome_conferencia[0]))) rejeitado = 1;
        if (ano == 0) rejeitado = 1;
        if (pag_ini == 0) rejeitado = 1;
        if (pag_fin == 0) rejeitado = 1;
        if (((pag_fin - pag_ini) + 1) < min_pag) rejeitado = 1;

        //  if (rejeitado)
        //      printf("%s\n", inteiro);

        if (!rejeitado) {
            tmpArt = (Artigo*) malloc(sizeof (Artigo));
           // tmpArt->autores = (char*) calloc(len, sizeof (char));
           // strlcpy(tmpArt->autores, trim(lista_autores), strlen(lista_autores));
            tmpArt->numAutores = numeroAutores(trim(lista_autores));
            tmpArt->ano = ano;
            processaAutores(lista_autores);
        }
    }

   // if (!rejeitado)
   //     if (tmpArt->numAutores == 9)
   //         printf("%s %s %d\n", nome_conferencia, tmpArt->inteiro, tmpArt->numAutores);


    return tmpArt;
}


int rejeita_dados(const char* str) {
    char* p;
    char* copia;
    copia = strLower(str);
    int rejeita = 0;

    p = strstr(copia, "in memory of");
    if (p) rejeita = 1;

    if (!rejeita) {
        char* p = strstr(copia, "editorial");
        if (p) rejeita = 1;
    }
    if (!rejeita) {
        char* p = strstr(copia, "preface");
        if (p) rejeita = 1;
    }
    if (!rejeita) {
        char* p = strstr(copia, "errata");
        if (p) rejeita = 1;
    }
    if (!rejeita) {
        char* p = strstr(copia, "obituary");
        if (p) rejeita = 1;
    }
    if (!rejeita) {
        char* p = strstr(copia, "isbn");
        if (p) rejeita = 1;
    }
    return rejeita;
}

char * strLower(const char *str) {
    int len = strlen(str);
    int i;
    char* copia = (char*) malloc(sizeof (char) *len);

    for (i = 0; i < len; i++)
        copia[i] = tolower(str[i]);

    return copia;
}




//int ordena_Ano() {
//
//}
/*
int conta_Autores(char* str) {
    //    conta o numero de virgulas no campo autor e soma 1 = numero de autores
    int len = strlen(str);
    int i, cnt = 1;
    for (i = 0; i < len; i++)
        if (str[i] == ',') cnt++;
    return cnt;
}
 */
