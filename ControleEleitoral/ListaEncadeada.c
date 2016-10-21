#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CedulaDeEleicao.h"
#include "ListaEncadeada.h"

/*Inicializa a lista.*/
Lista criaLista(){
    Lista lista;
    lista = (Lista) malloc(sizeof(tipo_lista));

    if(!lista) return NULL;

    lista->first = NULL;
    lista->last = NULL;
    lista->tamanho = 0;
    return lista;
}/*Lista criaLista()*/

/*Retorna a quantidade de elementos na lista.*/
int tamanhoLista(Lista lista){
    return lista->tamanho;
}/*int tamanhoLista(Lista lista)*/

/*Verifica se a lista est� vazia, se tiver, retorna 1. Caso n�o esteja retorna 0.*/
int listaVazia(Lista lista){
    if(lista->tamanho == 0)
        return 1;
    return 0;
}/*int listaVazia(Lista lista)*/

/*Insere um novo elemento na lista, caso este n�o j� esteja cadastrado. Retorna 1
  se conseguir e 0 caso n�o seja poss�vel realizar a inser��o.*/
int insereLista(Lista lista, cedulaEleitoral cedula){
    tipo_nodo *nodo;
    nodo = lista->first;

    /*Realiza a busca para verificar se a j� esta presente na lista.*/
    while(nodo){
        if(!strcmp(cedula.tituloEleitor, nodo->cedula.tituloEleitor))
            break;
        nodo = nodo->proximo;
    }

    /*Verifica se foi n�o foi encontrado, caso n�o tenha sido realiza a inser��o.*/
    if(!nodo){
        nodo = (tipo_nodo*) malloc(sizeof(tipo_nodo));
        nodo->cedula = cedula;
        nodo->proximo = NULL;

        /*Verifica se � o primeiro nodo a ser inserido*/
        if(!lista->first)
            lista->first = nodo;
        else
            lista->last->proximo = nodo;
        lista->last = nodo;
        lista->tamanho++;
        return 1;
    }
    return 0;
}/*int insereLista(Lista lista, cedulaEleitoral cedula)*/

/*Remove um item inserido na lista, caso este seja localizado. Retorna 1
  caso consiga remover e 0 caso n�o consiga.*/
int removeLista(Lista lista, tipoChave chave, cedulaEleitoral *cedula){
    tipo_nodo *nodo, *anterior;
    nodo = lista->first;
    while(nodo){
        if(!strcmp(chave, nodo->cedula.tituloEleitor))
            break;
        anterior = nodo;
        nodo = nodo->proximo;
    }

    if(nodo){
        if(lista->first == nodo)
            lista->first = nodo->proximo;
        else
            if(lista->last == nodo){
                lista->last = anterior;
                anterior->proximo = NULL;
            }
            else
                anterior->proximo = nodo->proximo;
            *cedula = nodo->cedula;
            free(nodo);
            lista->tamanho--;
            return 1;
    }
    return 0;
}/*int removeLista(Lista lista, tipoChave chave, cedulaEleitoral *cedula)*/

/*Atualiza as informa��es de um nodo caso este j� esteja presente na lista.
  Retorna 1 caso a atualiza��o seja bem sucedida e 0 caso n�o seja poss�vel
  atualizar.*/
int atualizarLista(Lista lista, tipoChave chave, cedulaEleitoral cedula){
    tipo_nodo *nodo;

    if(listaVazia(lista)) return 0;

    nodo = lista->first;
    while(nodo){
        if(!strcmp(chave, nodo->cedula.tituloEleitor))
        {
            nodo->cedula = cedula;
            return 1;
        }
        nodo = nodo->proximo;
    }
    return 0;
}/*int atualizarLista(Lista lista, tipoChave chave, cedulaEleitoral cedula)*/

/*Pesquisa se uma chave est� presente na lista, caso esteja retorna uma c�pia
  da struct como refer�ncia e retorna 1 avisando que a busca foi bem sucedida.
  Caso n�o encotre retorna 0.*/
int pesquisarLista(Lista lista, tipoChave chave, cedulaEleitoral *cedula){
    tipo_nodo *nodo;

    if(listaVazia(lista)) return 0;

    nodo = lista->first;
    while(nodo){
        if(!strcmp(chave,nodo->cedula.tituloEleitor))
        {
            *cedula = nodo->cedula;
            return 1;
        }
        nodo = nodo->proximo;
    }/*while(nodo)*/
    return 0;
}/*int pesquisarLista(Lista lista, tipoChave chave, cedulaEleitoral *cedula)*/

/*Libera o espa�o alocado para a lista.*/
void terminaLista(Lista lista){
    tipo_nodo *nodo;
    while(lista->first != NULL){
        nodo = lista->first;
        lista->first = lista->first->proximo;
        free(nodo);
    }
    free(lista);
}/*void terminaLista(Lista lista)*/
