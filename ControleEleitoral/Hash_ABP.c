#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"Hash_ABP.h"
#include"abp.h"
#include"CedulaDeEleicao.h"

HashTabelaArvore criaTabelaHashArvore(unsigned int m, unsigned int numeroPesos){
    HashTabelaArvore t = (HashTabelaArvore)malloc(sizeof(tipo_tabela));
    if(t){
        int i;
        t->itens = (apontador*)malloc(sizeof(TipoNodo)*m);
        for(i = 0;i<m;i++){
            t->itens[i] = (apontador)malloc(sizeof(TipoNodo));
            t->itens[i] = inicializa_abp();
        }
        t->M = m;
        t->tamanho = 0;
        t->numero = numeroPesos;
        /*Inicializado o vetor de pesos*/
        srand(time(NULL));
        t->vetorPesos = (tipoPesos) malloc(sizeof(unsigned int) * t->numero);
        for(i = 0; i < t->numero; i++)
            t->vetorPesos[i] = (unsigned int) rand();

    }
    return t;
}

/*Calcula e retorna a posição em que a nova chave deve ser inserida na tabela.*/
unsigned int hashArvore(HashTabelaArvore tabela, tipoChave chave){
    unsigned int soma = 0, i, tamanho;
    tamanho = strlen(chave);
    for(i = 0; i < tamanho; i++)
        soma += chave[i] * tabela->vetorPesos[i];
    return soma % tabela->M;
}

int insereItemTabelaArvore(HashTabelaArvore t,cedulaEleitoral e){
    unsigned int posicao = hashArvore(t,e.tituloEleitor);
    if(insere_abp(e,&t->itens[posicao]))
        return 1;
    return 0;
}

int removeItemTabelaArvore(HashTabelaArvore t,tipoChave chave,cedulaEleitoral* e){
    unsigned int posicao = hashArvore(t,chave);
    if(retira_abp(chave,e,&t->itens[posicao]))
        return 1;
    return 0;
}

int pesquisaItemTabelaArvore(HashTabelaArvore t,tipoChave chave,cedulaEleitoral* e){
    unsigned int posicao = hashArvore(t,chave);
    if(pesquisa_abp(chave,e,t->itens[posicao]))
        return 1;
    return 0;
}

void terminaTabelaArvore(HashTabelaArvore t){
    int i;
    for(i= 0;i<t->M;i++){
        free(t->itens[i]);
    }
    free(t);
}


