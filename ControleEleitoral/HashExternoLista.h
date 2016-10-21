#ifndef HASHEXTERNOLISTA_H_INCLUDED
#define HASHEXTERNOLISTA_H_INCLUDED

#include "ListaEncadeada.h"
#include "CedulaDeEleicao.h"

/*Define a estrutura do tipo tabela que será utilizada.*/
typedef struct{
    Lista listas;
    unsigned int M,
                 tamanho,
                 numeroPesos,
                 *vetorPesos;
}tipoTabelaLista;

typedef tipoTabelaLista *TabelaLista;

TabelaLista criarTabelaLista(unsigned int, unsigned int);
int inserirItemTabelaLista(TabelaLista, cedulaEleitoral);
int pesquisarItemTabelaLista(TabelaLista, tipoChave, cedulaEleitoral*);
int atualizarItemTabelaLista(TabelaLista, tipoChave, cedulaEleitoral);
int removerItemTabelaLista(TabelaLista, tipoChave, cedulaEleitoral*);
void terminarTabelaLista(TabelaLista);

#endif
