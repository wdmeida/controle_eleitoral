#ifndef HASH_ABP_H_INCLUDED
#define HASH_ABP_H_INCLUDED

#include"CedulaDeEleicao.h"
#include"abp.h"

typedef struct{
    apontador *itens;
    unsigned int M;
    unsigned int tamanho;
    unsigned int *vetorPesos,
                  numero;
}tipo_tabela;

typedef tipo_tabela* HashTabelaArvore;

HashTabelaArvore criaTabelaHashArvore(unsigned int m, unsigned int numeroPesos);

int insereItemTabelaArvore(HashTabelaArvore,cedulaEleitoral);
int removeItemTabelaArvore(HashTabelaArvore,tipoChave,cedulaEleitoral*);
int pesquisaItemTabelaArvore(HashTabelaArvore,tipoChave,cedulaEleitoral*);
void terminaTabelaArvore(HashTabelaArvore);

#endif
