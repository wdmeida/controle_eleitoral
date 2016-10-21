#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

#include "CedulaDeEleicao.h"

/*Define a estrutura de cada nodo da lista*/
typedef struct nodoLista{
    cedulaEleitoral cedula;
    struct nodoLista *proximo;
}tipo_nodo;

/*Define os campos da lista.*/
typedef struct{
    tipo_nodo *first, *last;
    int tamanho;
}tipo_lista;

typedef tipo_lista *Lista;

/*Define as operações da Lista encadeada.*/
Lista criaLista();
int tamanhoLista(Lista);
int listaVazia(Lista);
int insereLista(Lista, cedulaEleitoral);
int removeLista(Lista, tipoChave, cedulaEleitoral*);
int atualizarLista(Lista, tipoChave, cedulaEleitoral);
int pesquisarLista(Lista, tipoChave, cedulaEleitoral*);
void terminaLista(Lista);

#endif
