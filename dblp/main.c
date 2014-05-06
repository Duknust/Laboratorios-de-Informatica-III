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
#include "util.h"
#include "hashing.h"
//#include "mod_estatistico.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //    char *tmp = readJ("j-Exemplo.txt");
    Artigo * conf;
    Artigo * rev;
    //LL* artigos;
    int opcao = 0;
    int nConfs = 0;
    int nRevs = 0;
    int revsRej = 0;
    int confsRej = 0;
    int teste = 0;
    char **jlist;
    char *a;
    char *tmp = (char*) malloc(sizeof (char) *50);
    int min_pag;
    char *a1 = "Igor", *a2 = "Ze", *a3 = "Joao", *a4 = "Nelson", *autores = "Joao, Ze, Manel, Igor";
    char autor1[50] = {};
    char autor2[50] = {};


    // printf ("%d",contemNum("oigaf 313daj"));
    // printf("%d",contemLet("242a315"));
    //  read_list("/Users/duarteduarte/Downloads/LI3-4TST(1)/teste3/", "listac.txt");
    //  insereOrd(artigo,lista);
    //  insereOrd(artigo2,lista);
    gestorFilehandling(CAMINHO, "lista.txt");
    //read_list(CAMINHO, "lista.txt");
    //   read_list("/Users/duarteduarte/Downloads/LI3-4TST(1)/teste1/", "listac.txt");
    //processaAutores(autores);

    //initHT();
    /* insereAutorHt(a1, a1);
     addCoAutor(a1, a2);
     addCoAutor(a1, a3);
     insereAutorHt(a1,a1);
     insereAutorHt(a2, a2);
     addCoAutor(a2, a4);
     addCoAutor(a2, a4);*/


 printf("\n");
    while (opcao != 5) {
       
        printf(".----- MENU -----\n");
        printf(". 1 - Determinar com quantos outros autores escreveu artigos\n");
        printf(". 2 - Numero de artigos em comum\n");
        printf(". 3 - Par ou pares de autores com maior numero de artigos em comum\n");
        printf(". 4 - Top 10 de autores com maior numero de co-autores\n");
        printf(". 5 - Sair\n");
        printf("\n");
        printf(". Insira a sua opcao:");
        printf("\n> ");

                scanf("%d", &opcao);


        if (opcao == 1) {
            printf(". Insira o nome do autor > ");
            gets(&autor1);
            //printf("%s", autor1);
            q1qntsAutoresEscreveu(autor1);
        }
        if (opcao == 2) {
            printf(". Insira o nome do 1o autor > ");
            gets(&autor1);
            //fflush(stdout);
            printf("\n. Insira o nome do 2o autor > ");
            gets(&autor2);
            q2qntsArtigosComum(autor1, autor2);
        }
        if (opcao == 3) {
            q3maxArtigosComum();
        }
        if (opcao == 4) {
            q4Top10Artigos();
        }
        //fflush(stdout);
        printf("\n");
    }

    //printf("%d na lista\n",qntsHT());
    //q1qntsAutoresEscreveu("Wei Wang");
    //q2qntsArtigosComum("Wei Wang", "Yiqi Lu");
    //printf("q1: %d\n", q1qntsAutoresEscreveu("Wei Wang"));
    //printf("q1-a1: %d\n", q1qntsAutoresEscreveu("Wei Wang"));
    //printf("q2: %d\n", q2qntsArtigosComum("Wei Wang", "Yiqi Lu"));
    //printf("q2-a1,a2: %d\n", q2qntsArtigosComum(a1, a2));
    //q3maxArtigosComum(); // ESTA DESTROI A LISTA MAS A IDEIA ESTÁ LÁ :D
    //q4Top10Artigos();
    //printf("%d na lista no fim\n",qntsHT());
    //    artigos=returnArtigos();
    //   stats=listaTotalAnos(artigos);

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

