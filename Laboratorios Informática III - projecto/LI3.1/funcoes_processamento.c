#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes_processamento.h"
#include "util.h"
#include "estruturas.h"
#include "mod_estatistico.h"



#define MAXSTRING 2000
#define TMPTAM 200

int retira_dados_REV(const char *dados, Artigo* art) {

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
    char tmp[TMPTAM];
    int rejeitado = 0;
    int len = strlen(dados);
    //REV * rev;

    rejeitado = (rejeita_dados(dados));
    if (art != NULL && !rejeitado) {

        for (i = 0; i<len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            inteiro[j++] = dados[i]; /*começa um a frente no proximo*/
        }
  //      printf("-------\n");
      // printf("int-> %s\n", inteiro);
      //  printf("-------\n");

        j = 0;
        for (i; i < len && dados[i] != ':' && dados[i] != '\0'; i++) {
            lista_autores[j++] = dados[i]; /*começa um a frente no proximo*/
        }
       // printf("autores-> %s\n", lista_autores);

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
        clear_str(&tmp, TMPTAM);
        for (i += 2; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        volume_revista = atoi(tmp);
       // printf("volume-> %d\n", volume_revista);


        j = 0;
        clear_str(&tmp, TMPTAM);
        if (dados[i] == ' ') i++;
        if (dados[i] == '(') i++;
        for (i; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        num_revista = atoi(tmp);
        //printf("numRev-> %d\n", num_revista);

        j = 0;
        clear_str(&tmp, TMPTAM);
        if (dados[i] == ')')i++;
        if (dados[i] == ':')i++;
        for (i; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_ini = atoi(tmp);
        //printf("PI-> %d\n", pag_ini);

        j = 0;
        clear_str(&tmp, TMPTAM);
        if (dados[i] == ' ') i++;
        if (dados[i] == '-') i++;
        for (i; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        pag_fin = atoi(tmp);
        //printf("PF-> %d\n", pag_fin);

        j = 0;
        clear_str(&tmp, TMPTAM);
        while (!(isdigit(dados[i])) && i < len) i++;
        for (i; i < len && dados[i] != ')' && dados[i] != '\0'; i++) {
            tmp[j++] = dados[i];
        }
        ano = atoi(tmp);
        //printf("ano-> %d\n", ano);
        //      if (titulo == ) rejeitado = 1;
        //      if (nome_revista == {})rejeitado =1;
       // if ((strcmp("", lista_autores) == 0) || (lista_autores[0] == '\0')) rejeitado = 1;
       // if ((strcmp("", titulo) == 0) || (titulo[0] == '\0')) rejeitado = 1;
       // if ((strcmp("", nome_revista) == 0) || (nome_revista == '\0')) rejeitado = 1;
       // if ((strcmp("", sigla) == 0) || (sigla == '\0')) rejeitado = 1;
        if (volume_revista == 0) rejeitado = 1;
        if (num_revista == 0) rejeitado = 1;
        if (pag_ini == 0) rejeitado = 1;
        if (pag_fin == 0) rejeitado = 1;
        if (ano == 0) rejeitado = 1;
        if (((pag_fin - pag_ini) + 1) < min_pag) rejeitado = 1;
        if (!rejeitado) {

            strcpy(&art->inteiro, trim(&inteiro));
            art->numAutores = numeroAutores(trim(lista_autores));
            art->ano = ano;
            art->tipoArt = REVI;
        }
    }

    return rejeitado;
}

int retira_dados_CONF(const char *dados, Artigo* art) {

    int i, j = 0;
    char nome_conferencia [MAXSTRING] = {};
    char inteiro[MAXSTRING] = {};
    char lista_autores [MAXSTRING] = {};
    char titulo[MAXSTRING] = {};
    int pag_ini;
    int pag_fin;
    int ano;
    char tmp[200] = {};
    int rejeitado = 0;
    int len = strlen(dados);

    rejeitado = (rejeita_dados(dados));

    if (art != NULL && !rejeitado) {

        for (i = 0; i < len && isdigit(dados[i]) && dados[i] != '\0'; i++) {
            inteiro[j++] = dados[i];
        }

        //printf("------\n", inteiro);
    //    printf("int-> %s\n", inteiro);
       // printf("------\n", inteiro);

        j = 0;
        for (i; i < len && dados[i] != '\0' && dados[i] != ':'; i++) {
            lista_autores[j++] = dados[i];
        }
    //   printf("autores-> %s\n", lista_autores);

        j = 0;
        if (i<len) i++;
        for (i; i < len && dados[i] != '\0' && dados[i] != '.'; i++) {
            titulo[j++] = dados[i];
        }
    //     printf("titulo-> %s\n", titulo);
         i++;
         if(isdigit(dados[i])) return 1;
        j = 0;
        // for (i = i + 2; dados[i] != ' '&& dados[i] != '\0'; i++) {
        if (i<len) i++;
        for (i; i < len && dados[i] != '\0' && (!isdigit(dados[i])); i++) {
            nome_conferencia[j++] = dados[i];
        }
   //     strcpy(nome_conferencia,"REJECT");
        //if (isdigit(dados[i])) printf ("NAO");
        //if (isdigit(dados[i])) printf ("%c \n",dados[i]);
     //   printf("nomeConf-> %s\n", nome_conferencia);
        //trim(nome_conferencia);
        if (isdigit(nome_conferencia[0])) return 1; //TA AQUI A CENA DO ERRO, ESTA A PROCURAR FORA E ESTOURA!!

        j = 0;
        clear_str(&tmp, TMPTAM);
        for (i; i < len && dados[i] != '\0' && dados[i] != ':' ; i++) {
            tmp[j++] = dados[i];
        }
        ano = atoi(tmp);
        //printf("ano-> %d\n", ano);

        j = 0;
        clear_str(&tmp, TMPTAM);
        if (i<len) i++;
        for (i; i < len && dados[i] != '\0' && dados[i] != '-'; i++) {
            tmp[j++] = dados[i];
        }
        pag_ini = atoi(tmp);
        //printf("PI-> %d\n", pag_ini);

        j = 0;
        clear_str(&tmp, TMPTAM);
        if (i<len) i++;
        for (i; i < len && dados[i] != '\0' && isdigit(dados[i]); i++) {
            tmp[j++] = dados[i];
        }
        pag_fin = atoi(tmp);
        //printf("PF-> %d\n", pag_fin);
        clear_str(&tmp, TMPTAM);

      //  if ((strcmp("", lista_autores) == 0) || (lista_autores[0] == '\0')) rejeitado = 1;
        if (numeroAutores(trim(lista_autores))<=0) rejeitado = 1;
        if ((strcmp("", titulo) == 0) || (titulo[0] == '\0')) rejeitado = 1;
      //  if ((strcmp("", nome_conferencia) == 0) || (nome_conferencia == '\0')) rejeitado = 1;
        if (nome_conferencia==NULL) return 1;
        if (strcmp("",nome_conferencia)==0) rejeitado = 1;
       // if (strcmp("REJECT",nome_conferencia)==0) rejeitado = 1;
       //if (!isalnum(trim(nome_conferencia[0]))) rejeitado = 1;
        if (ano == 0) rejeitado = 1;
        if (pag_ini == 0) rejeitado = 1;
        if (pag_fin == 0) rejeitado = 1;
        if (((pag_fin - pag_ini) + 1) < min_pag) rejeitado = 1;
        if (!rejeitado) {

            //conf = (CONF*) malloc(sizeof (CONF));
            strcpy(&art->inteiro, trim(&inteiro));
            art->numAutores = numeroAutores(trim(lista_autores));
            art->ano = ano;
            art->tipoArt = CONFE;
        }
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
