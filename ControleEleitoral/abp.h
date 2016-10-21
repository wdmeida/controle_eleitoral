#ifndef ABP_H_INCLUDED
#define ABP_H_INCLUDED

#include"CedulaDeEleicao.h"

typedef struct Nodo *apontador;
typedef struct Nodo{
    cedulaEleitoral info;
    apontador esq,dir;
}TipoNodo;

apontador inicializa_abp();

int pesquisa_abp(tipoChave,cedulaEleitoral*,apontador);
int insere_abp(cedulaEleitoral,apontador*);
int retira_abp(tipoChave, cedulaEleitoral*,apontador*);
void termina_abp(apontador);
void percorre_in_ordem(apontador);
#endif
