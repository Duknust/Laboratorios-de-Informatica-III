/* 
 * File:   main.c
 * Author: duarteduarte
 *
 * Created on 20 de Fevereiro de 2013, 20:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "funcoes_processamento.h"
#include "filehandling.h"
#include "mod_ListasLigadas.h"
#include "util.h"
#include "mod_estatistico.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //    char *tmp = readJ("j-Exemplo.txt");
    Artigo * conf;
    Artigo * rev;
    LLptr artigos;
    BinTree *stats=NULL;
    int nConfs=0;
    int nRevs=0;
    int revsRej=0;
    int confsRej=0;
    int teste=0;
    char **jlist;
    char *a;
    char *tmp = (char*)malloc(sizeof(char)*50);
    int min_pag;
    
  //  read_list("/Users/duarteduarte/Downloads/LI3-4TST(1)/teste3/", "listac.txt");
    read_list(CAMINHO, "lista.txt", &nConfs, &nRevs, &confsRej, &revsRej);
 //   read_list("/Users/duarteduarte/Downloads/LI3-4TST(1)/teste1/", "listac.txt");
    logStats(nConfs, nRevs, confsRej, revsRej);
    
//    artigos=returnArtigos();
//    stats=listaTotalAnos(artigos);
    
  //  teste=numeroAutores(trim(" a,141 "));
  //  printf ("%d",teste);
  //  strcpy(tmp,&" o Igor SfnA\n");
 //   tmp = trim(tmp);
    //printf("%s",tmp);
    
   // teste = conta_Autores("daf,afauhg,agua,gausada,adaffaub");
   // printf("%d\n",teste);
 //   nConfs = readC("c-Exemplo.txt");
    
 //   nRevs = readJ("j-Exemplo.txt");
    /*strcpy(&dados, tmp);
    rev=retira_dados_REV();
    a2.revistas = *rev;
     */
    //insere(&a1, CONFE);
    //insere(&a2, REVI);

   // printf("jdhgfdjsh\n");
   // imprimeElems();
    
    //printf("\nNumero de elementos: %d\n", comprimento(artigos));
    //remover(&a1);
    //imprimeElems();

    return (EXIT_SUCCESS);
}

