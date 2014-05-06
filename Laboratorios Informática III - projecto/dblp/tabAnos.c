#include <stdlib.h>
#include <stdio.h>
#include "funcoes_processamento.h"
#include "filehandling.h"
#include "estruturas.h"
#include "util.h"

NautDIN *insereORDtad(NautDIN *din, int ano, int nautores) {
    NautDIN *tmp = din, *aux = NULL;
    int exists = 0, insere = 0;



    aux = (NautDIN *) malloc(sizeof (NautDIN));
    aux->ano = ano;
    aux->nArtigos = 1;
    aux->nAutores = nautores;
    aux->seg = NULL;

    if (din == NULL) {
        din = aux;
    } else {
        tmp = din;
        if (ano <= tmp->ano || (ano == tmp->ano && nautores < tmp->nAutores)) {
            aux->seg = din;
            din = aux;
            exists = 1;
        } else {
            while (tmp != NULL && !exists) {
                if (tmp->ano == ano && tmp->nAutores == nautores) {
                    tmp->nArtigos++;
                    exists = 1;
                } else if (tmp->seg != NULL) {
                    if (ano == tmp->ano && ano == tmp->seg->ano) {
                        if (nautores > tmp->nAutores && nautores < tmp->seg->nAutores)
                            insere = 1;
                    } else if (ano >= tmp->ano && ano < tmp->seg->ano)
                        insere = 1;
                    else if (ano > tmp->ano && ano == tmp->seg->ano)
                        if (nautores < tmp->seg->nAutores)
                            insere = 1;

                    //&& ((ano > tmp->ano && ano < tmp->seg->ano)
                    //|| (ano == tmp->seg->ano && nautores < tmp->seg->nAutores)
                    //|| (ano == tmp->ano && nautores > tmp->nAutores && (nautores < tmp->seg->nAutores || ano <= tmp->seg->ano)))) {
                    if (insere) {
                        aux->seg = tmp->seg;
                        tmp->seg = aux;
                        exists = 1;
                    }
                } else if (tmp->seg == NULL) {
                    tmp->seg = aux;
                    exists = 1;
                }

                tmp = tmp->seg;
            }
        }
    }


    return din;
}

void *initTA() {
    int i, j;
    tabelaAutores = (TabAutores *) malloc(sizeof (TabAutores));
    tabelaAutores->nSta = (NautSTA*) malloc(sizeof (NautSTA));
    for (i = 0; i < MAX_ANOS; i++)
        for (j = 0; j < 10; j++)
            tabelaAutores->nSta->nAutSTA[i][j] = 0;
    tabelaAutores->nDin = NULL;
}

void *insertTA(TabAutores *tabA, int ano, int nautores) {

    if (nautores <= 10 && ano >= BASEYEAR) {
        tabA->nSta->nAutSTA[(ano - BASEYEAR)][nautores - 1]++;
    } else {
        tabA->nDin = insereORDtad(tabA->nDin, ano, nautores);
    }
}

// void *procuraTA(TabAutores *tabA, int ano) {
// }

int numeroCOLAutores(TabAutores *tabA, int nautores) {
    int i, res = 0;
    if (nautores <= 10) {
        for (i = 0; i < MAX_ANOS; i++)
            res += tabA->nSta->nAutSTA[i][nautores - 1];
    }
    return res;
}

int numeroLLAutores(NautDIN *din, int nautores) {
    int res = 0;
    NautDIN *tmp = din;
    while (tmp != NULL) {
        printf("%d\n", tmp->nAutores);
        if (tmp->nAutores == nautores)
            res += tmp->nArtigos;
        tmp = tmp->seg;
    }
    return res;
}

int prints(NautDIN *din) {
    while (din != NULL) {
        printf("%d", din->nAutores);
        din = din->seg;
    }
    return 0;
}

int anosAutoresPercentagem(int ano) {
    int j = 0, total = 0, res = 0, notfound = 0;
    float pct = 0.0;
    float tmpX = 0;

    NautDIN *tmp = NULL;
    for (j = 0; j < 10; j++)
        total += tabelaAutores->nSta->nAutSTA[ano - BASEYEAR][j];

    tmp = tabelaAutores->nDin;
    while (tmp && !notfound) {
        if (tmp->ano == ano)
            total += tmp->nArtigos;
        else if (tmp->seg != NULL && ano < tmp->seg->ano)
            notfound = 1;

        tmp = tmp->seg;
    }

    if (total != 0) {
        for (j = 0; j < 10; j++) {
            tmpX = (float) (tabelaAutores->nSta->nAutSTA[ano - BASEYEAR][j]);
            pct = (tmpX / total);
            logAnosAutoresPercentagem(ano, j + 1, pct * 100);
        }

        notfound = 0;
        tmp = tabelaAutores->nDin;
        while (tmp && !notfound) {
            if (tmp->ano == ano) {
                pct = ((float) (tmp->nArtigos) / total);
                logAnosAutoresPercentagem(ano, tmp->nAutores, pct * 100);
            } else if (tmp->seg != NULL && tmp->seg->ano > ano)
                notfound = 1;

            tmp = tmp->seg;
        }

    } else
        res = -1;



    return res;
}

int intervalosAnos(int anoInicial, int anoFinal) {
    int i = 0, j = 0, res = 0;
    NautDIN *tmp = NULL;

    for (i = anoInicial - BASEYEAR; i <= anoFinal - BASEYEAR; i++)
        for (j = 0; j < 10; j++)
            res += (tabelaAutores->nSta->nAutSTA[i][j] != 0) ? tabelaAutores->nSta->nAutSTA[i][j] : 0;

    tmp = tabelaAutores->nDin;
    while (tmp) {
        if (tmp->ano >= anoInicial && tmp->ano <= anoFinal)
            res += tmp->nArtigos;

        tmp = tmp->seg;
    }

    logIntervalo(anoInicial, anoFinal, res);

    return 0;
}

Status *insereStatusOrd(Status *status, int nAutores, int nArtigos) {
    Status *tmp = NULL, *aux = NULL;
    int inserido = 0;
    // int para = 0;

    tmp = (Status *) malloc(sizeof (Status));
    tmp->nArtigos = nArtigos;
    tmp->nAutores = nAutores;
    tmp->seg = NULL;

    if (status == NULL) {
        status = tmp;
    } else {
        aux = status;

        if (nAutores < aux->nAutores) {
            tmp->seg = status;
            status = tmp;
        } else {
            while (aux != NULL && !inserido) {
                if (aux->seg != NULL && nAutores > aux->nAutores && nAutores < aux->seg->nAutores) {
                    tmp->seg = aux->seg;
                    aux->seg = tmp;
                    inserido = 1;
                } else if (nAutores == aux->nAutores) {
                    aux->nArtigos += nArtigos;
                    inserido = 1;
                } else if (aux->seg == NULL) {
                    aux->seg = tmp;
                    inserido = 1;
                }

                aux = aux->seg;
            }
        }
    }

    return status;
}

void *insereStatus(Status **status, int nAutores, int nArtigos) {
    if (*status == NULL) {
        (*status) = (Status *) malloc(sizeof (Status));
        (*status)->nAutores = nAutores; //LALALA
        (*status)->nArtigos = nArtigos; //LALALA
        (*status)->seg = NULL; //LALALA
    } else
        (*status) = insereStatusOrd(*status, nAutores, nArtigos);
}

int nAutoresArtigo() {
    int i = 0, j = 0, res=0;
    NautDIN *tmp = NULL;
    Status *status = NULL, *tmpStatus = NULL;

    for (j = 0; j < 10; j++) {
        for (i = 0; i < MAX_ANOS; i++)
            res += tabelaAutores->nSta->nAutSTA[i][j];
        logAutoresArtigo(j + 1, res);
        res = 0;
    }
    tmp = tabelaAutores->nDin;

    while (tmp != NULL) {
        insereStatus(&status, tmp->nAutores, tmp->nArtigos);
        tmp = tmp->seg;
    }
    tmpStatus = status;
    while (tmpStatus != NULL) {
        logAutoresArtigo(tmpStatus->nAutores, tmpStatus->nArtigos);
        tmpStatus = tmpStatus->seg;
    }

    //freeStatus(status);

    return 0;
}

int anoAutoresArtigo() {
    int i = 0, j = 0, res;
    NautDIN *tmp = NULL;
    int sair = 0;
    tmp = tabelaAutores->nDin;
    for (i = 0; i < MAX_ANOS; i++) {
        for (j = 0; j < 10; j++) {
            res = tabelaAutores->nSta->nAutSTA[i][j];
            if (res != 0)
                logAnAutArt(i + BASEYEAR, j + 1, res);
        }
        sair = 0;
        while (tmp && !sair) {
            if (tmp->ano == (i + BASEYEAR) && tmp->nArtigos != 0) {
                res = tmp->nArtigos;
                logAnAutArt(i + BASEYEAR, tmp->nAutores, res);
                tmp = tmp->seg;
            } else if (tmp->ano < (i + BASEYEAR)) tmp = tmp->seg;
            else sair = 1;
        }
        res = 0;
        // if (res != 0)
        //     logAnAutArt(i + BASEYEAR, j + 1, res);
    }
    //tmp = tabelaAutores->nDin;
    //while (tmp) {
    //    logAnAutArt(tmp->ano, tmp->nAutores, tmp->nArtigos);
    //    tmp = tmp->seg;
    //}
    return 0;
}

