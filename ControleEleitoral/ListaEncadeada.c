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

/*Verifica se a lista está vazia, se tiver, retorna 1. Caso não esteja retorna 0.*/
int listaVazia(Lista lista){
    if(lista->tamanho == 0)
        return 1;
    return 0;
}/*int listaVazia(Lista lista)*/

/*Insere um novo elemento na lista, caso este não já esteja cadastrado. Retorna 1
  se conseguir e 0 caso não seja possível realizar a inserção.*/
int insereLista(Lista lista, cedulaEleitoral cedula){
    tipo_nodo *nodo;
    nodo = lista->first;

    /*Realiza a busca para verificar se a já esta presente na lista.*/
    while(nodo){
        if(!strcmp(cedula.tituloEleitor, nodo->cedula.tituloEleitor))
            break;
        nodo = nodo->proximo;
    }

    /*Verifica se foi não foi encontrado, caso não tenha sido realiza a inserção.*/
    if(!nodo){
        nodo = (tipo_nodo*) malloc(sizeof(tipo_nodo));
        nodo->cedula = cedula;
        nodo->proximo = NULL;

        /*Verifica se é o primeiro nodo a ser inserido*/
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
  caso consiga remover e 0 caso não consiga.*/
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

/*Atualiza as informações de um nodo caso este já esteja presente na lista.
  Retorna 1 caso a atualização seja bem sucedida e 0 caso não seja possível
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

/*Pesquisa se uma chave está presente na lista, caso esteja retorna uma cópia
  da struct como referência e retorna 1 avisando que a busca foi bem sucedida.
  Caso não encotre retorna 0.*/
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

/*Libera o espaço alocado para a lista.*/
void terminaLista(Lista lista){
    tipo_nodo *nodo;
    while(lista->first != NULL){
        nodo = lista->first;
        lista->first = lista->first->proximo;
        free(nodo);
    }
    free(lista);
}/*void terminaLista(Lista lista)*/
