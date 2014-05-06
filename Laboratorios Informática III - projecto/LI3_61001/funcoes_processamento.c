#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes_processamento.h"
#include "util.h"
#include <ctype.h>


#define MAXSTRING 2000

int retira_dados_REV(char *dados, REV* rev) {

    int i = 0, j = 0;
    char inteiro[5] = {};
    char lista_autores [MAXSTRING] = {};
    char titulo [MAXSTRING] = {};
    char nome_revista [MAXSTRING] = {};
    char sigla[MAXSTRING] = {};
    int volume_revista;
    int num_revista;
    int pag_ini;
    int pag_fin;
    int ano;
    char tmp[50];
    int rejeitado = 0;
    int len=strlen(dados);
    //REV * rev;

    rejeitado = (rejeita_dados(dados));
    if (rev != NULL && !rejeitado) {

        for (i = 0; isdigit(dados[i]) && dados[i] != '\0'; i++) {
            inteiro[j++] = dados[i]; /*começa um a frente no proximo*/
        }
        printf("-------\n");
        printf("int-> %s\n", inteiro);
        printf("-------\n");

        j = 0;
        for (i; i<len && dados[i] != ':' && dados[i] != '\0'; i++) {
            lista_autores[j++] = dados[i]; /*começa um a frente no proximo*/
        }
        printf("autores-> %s\n", lista_autores);

        j = 0;
        for (++i;i<len && dados[i] != '.' && dados[i] != '\0'; i++) {
            titulo[j++] = dados[i]; /*começa um a frente no proximo*/
        }
        printf("titulo-> %s\n", titulo);
        
        if (dados[i]!='\0' || dados[i]!='\n'){
            
        j = 0;
        for (++i; i<len && dados[i] != '(' && dados[i] != '\0'; i++) { /*neste caso tem de ficar o parentesis, como ponho?*/
            nome_revista[j++] = dados[i];
        }
        printf("nomeRev-> %s\n", nome_revista);

        j = 0;
        for (++i; i<len && dados[i] != ')' && dados[i] != '\0'; i++) { /*neste caso tem de ficar o parentesis, como ponho?*/
            sigla[j++] = dados[i];
        }
        printf("sigla-> %s\n", sigla);
        }

        j = 0;
        clear_str(&tmp, 50);
        for (i += 2; i<len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        volume_revista = atoi(tmp);
        printf("volume-> %d\n", volume_revista);


        j = 0;
        clear_str(&tmp, 50);
        if (dados[i] == ' ') i++;
        if (dados[i] == '(') i++;
        for (i; i<len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        num_revista = atoi(tmp);
        printf("numRev-> %d\n", num_revista);

        j = 0;
        clear_str(&tmp, 50);
        if (dados[i] == ')')i++;
        if (dados[i] == ':')i++;
        for (i; i<len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_ini = atoi(tmp);
        printf("PI-> %d\n", pag_ini);

        j = 0;
        clear_str(&tmp, 50);
        if (dados[i] == ' ') i++;
        if (dados[i] == '-') i++;
        for (i; i<len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_fin = atoi(tmp);
        printf("PF-> %d\n", pag_fin);

        j = 0;
        clear_str(&tmp, 50);
        while (!(isdigit(dados[i])) && i<len) i++;
        for (i;i<len && dados[i] != ')' && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        ano = atoi(tmp);
        printf("ano-> %d\n", ano);
  //      if (titulo == ) rejeitado = 1;
  //      if (nome_revista == {})rejeitado =1;
        if (volume_revista == 0) rejeitado = 1;
        if (num_revista == 0) rejeitado = 1;
        if (pag_ini == 0) rejeitado = 1;
        if (pag_fin == 0) rejeitado = 1;
        if (ano == 0) rejeitado = 1;
        if (((pag_fin - pag_ini)+1) >= min_pag) {

            //rev=(REV*)malloc(sizeof(REV));
            strcpy(&rev->inteiro, trim(&inteiro));
            strcpy(&rev->lista_autores, trim(&lista_autores));
            strcpy(&rev->titulo, trim(&titulo));
            strcpy(&rev->nome_revista, trim(&nome_revista));
            strcpy(&rev->sigla, trim(&sigla));
            rev->volume_revista = volume_revista;
            rev->num_revista = num_revista;
            rev->pag_ini = pag_ini;
            rev->pag_fin = pag_fin;
            rev->ano = ano;
        } else
            rejeitado = 1;
    }

    return rejeitado;
}

int retira_dados_CONF(char *dados, CONF* conf) {

    int i, j = 0;
    char nome_conferencia [MAXSTRING] = {};
    char inteiro[MAXSTRING] = {};
    char lista_autores [MAXSTRING] = {};
    char titulo [MAXSTRING] = {};
    int pag_ini;
    int pag_fin;
    int ano;
    char tmp[50];
    int rejeitado = 0;
    int len = strlen(dados);

    rejeitado = (rejeita_dados(dados));

    if (conf != NULL && !rejeitado) {

        for (i = 0;i<len && isdigit(dados[i]) && dados[i] != '\0' ; i++) {
            inteiro[j++] = dados[i];
        }
        printf("int-> %s\n", inteiro);

        j = 0;
        for (i; i<len && dados[i] != ':' && dados[i] != '\0'; i++) {
            lista_autores[j++] = dados[i];
        }
        printf("autores-> %s\n", lista_autores);

        j = 0;
        for (++i;i<len && dados[i] != '.' && dados[i] != '\0'; i++) {
            titulo[j++] = dados[i];
        }
        printf("titulo-> %s\n", titulo);

        j = 0;
        // for (i = i + 2; dados[i] != ' '&& dados[i] != '\0'; i++) {
        for (++i ; i<len && (!isdigit(dados[i + 2])) && dados[i] != '\0'; i++) {
            nome_conferencia[j++] = dados[i];
        }
        printf("nomeConf-> %s\n", nome_conferencia);

        j = 0;
        clear_str(&tmp, 50);
        for (++i;i<len && dados[i] != ':' && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        ano = atoi(tmp);
        printf("ano-> %d\n", ano);

        j = 0;
        clear_str(&tmp, 50);
        for (++i;i<len && dados[i] != '-' && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_ini = atoi(tmp);
        printf("PI-> %d\n", pag_ini);

        j = 0;
        clear_str(&tmp, 50);
        for (++i;i<len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_fin = atoi(tmp);
        printf("PF-> %d\n", pag_fin);
        
        if (strcmp("",lista_autores)==0) rejeitado=1;
        if (strcmp("",titulo)==0) rejeitado=1;
        if (strcmp("",nome_conferencia)==0) rejeitado=1;
        if (ano == 0) rejeitado = 1;
        if (pag_ini == 0) rejeitado = 1;
        if (pag_fin == 0) rejeitado = 1;
        if (((pag_fin - pag_ini)+1) >= min_pag) {

            //conf = (CONF*) malloc(sizeof (CONF));
            strcpy(&conf->inteiro, trim(&inteiro));
            strcpy(&conf->lista_autores, trim(&lista_autores));
            strcpy(&conf->titulo, trim(&titulo));
            strcpy(&conf->nome_conferencia, trim(&nome_conferencia));
            conf->ano = ano;
            conf->pag_ini = pag_ini;
            conf->pag_fin = pag_fin;
        } else
            rejeitado = 1;
    }

    return rejeitado;
}

/*
int le_txt (){
  FILE * pFile;
  pFile = fopen ("myfile.txt","r");
  //COMO TIRO A PRIMEIRA LINHA!???? para guardar...
  
  fclose (pFile);
  return 0;
}
 */

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


int conta_Autores(char* str) {
//    conta o numero de virgulas no campo autor e soma 1 = numero de autores
    int len = strlen(str);
    int i, cnt=1;
    for(i=0;i<len;i++)
        if (str[i]==',') cnt++;
    return cnt;
}
