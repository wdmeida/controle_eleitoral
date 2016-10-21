#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ListaEncadeada.h"
#include "CedulaDeEleicao.h"
#include "HashExternoLista.h"

/*Aloca espa�o e cria a tabela hash.*/
TabelaLista criarTabelaLista(unsigned int m, unsigned int numeroPesos){
    TabelaLista tabela = (TabelaLista) malloc(sizeof(tipoTabelaLista));
    int i;
    if(tabela){

        /*Cria todas as posi��es da tabela (listas) e inicializa os campos.*/
        tabela->listas = (Lista) malloc(sizeof(tipo_lista)*m);
        tabela->M = m;
        tabela->tamanho = 0;
        tabela->numeroPesos = numeroPesos;

        /*Inicializado o vetor de pesos*/
        srand(time(NULL));
        tabela->vetorPesos = (tipoPesos) malloc(sizeof(unsigned int) * tabela->numeroPesos);
        for(i = 0; i < tabela->numeroPesos; i++)
            tabela->vetorPesos[i] = (unsigned int) rand();

        /*Inicializa cada lista dentro da tabela.*/
        for(i = 0; i < m; i++){
            tabela->listas[i].first = NULL;
            tabela->listas[i].last = NULL;
            tabela->listas[i].tamanho = 0;
        }
        return tabela;
    }
    return NULL;

}

/*Calcula e retorna a posi��o em que a nova chave deve ser inserida na tabela.*/
unsigned int hashLista(TabelaLista tabela, tipoChave chave){
    unsigned int soma = 0, i, tamanho;
    tamanho = strlen(chave);
    for(i = 0; i < tamanho; i++)
        soma += chave[i] * tabela->vetorPesos[i];
    return soma % tabela->M;
}

/*Insere um novo item na tabela se este j� n�o estiver cadastrado. Retorna 1 caso
  a inser��o seja realizada com sucesso e 0 caso n�o seja poss�vel inserir.*/
int inserirItemTabelaLista(TabelaLista tabela, cedulaEleitoral cedula){
    unsigned int posicao = hashLista(tabela, cedula.tituloEleitor);
    if(insereLista(&tabela->listas[posicao],cedula))
    {
        tabela->tamanho++;
        return 1;
    }
    return 0;
}

/*Pesquisa um elemento na tabela atrav�s de sua chave. Caso encontre, retorna o seu conte�do
  por refer�ncia e retorna 1 avisando que a busca foi bem sucedida. Caso n�o encontre retorna 0.*/
int pesquisarItemTabelaLista(TabelaLista tabela, tipoChave chave, cedulaEleitoral *cedula){
    unsigned int posicao = hashLista(tabela, chave);
    if(tabela->listas[posicao].tamanho == 0) return 0;
    if(pesquisarLista(&tabela->listas[posicao], chave, cedula))
        return 1;
    return 0;
}

/*Atualiza um elemento na tabela caso este seja localizado atrav�s de sua chave. Retorna
  1 caso a atualiza��o seja bem sucedida e 0 caso n�o seja poss�vel atualizar.*/
int atualizarItemTabelaLista(TabelaLista tabela, tipoChave chave, cedulaEleitoral cedula){
    unsigned int posicao = hashLista(tabela,chave);
    if(tabela->listas[posicao].tamanho == 0) return 0;
    if(atualizarLista(&tabela->listas[posicao], chave, cedula))
        return 1;
    return 0;
}

/*Remove um elemento na tabela atrav�s de sua chave. Caso encontre, retorna o seu conte�do
  por refer�ncia, apaga o elemento e retorna 1 para avisar que a exclus�o foi bem sucedida.
  Caso n�o encontre o elemento, retorna 0.*/
int removerItemTabelaLista(TabelaLista tabela, tipoChave chave, cedulaEleitoral *cedula){
    unsigned int posicao = hashLista(tabela, chave);
    if(tabela->listas[posicao].tamanho == 0) return 0;
    if(removeLista(&tabela->listas[posicao], chave, cedula))
    {
        tabela->tamanho--;
        return 1;
    }
    return 0;
}

/*Desaloca a mem�ria reservada para a cria��o da tabela.*/
void terminarTabelaLista(TabelaLista tabela){
    free(tabela->listas);
    free(tabela->vetorPesos);
    free(tabela);
}
