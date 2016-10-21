#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CedulaDeEleicao.h"
#include "HashDuplo.h"

/*Aloca o espa�o para a tabela, e inicializa todos os campos.*/
THashDupla criarTHashDupla(unsigned int m, unsigned int numeroPesos){
    THashDupla tabela = (THashDupla) malloc(sizeof(tipoHashDuplo));
    int i;

    if(tabela){
        /*Alocando o espa�o da tabela.*/
        tabela->cedula = (cedulaEleitoral*) malloc(sizeof(cedulaEleitoral) * m);

        /*Inicializando os atributos.*/
        tabela->M = m;
        tabela->quantidadeDados = 0;
        tabela->numeroPesos = numeroPesos;

        /*Aloca e inicializa os campos de controle.*/
        tabela->campoDeControle = (unsigned int*) malloc(sizeof(unsigned int) * m);
        for(i = 0; i < m; i++)
            tabela->campoDeControle[i] = 0;

        /*Aloca o vetor de pesos e inicializa as posi��es.*/
        tabela->vetorPesos = (tipoPesos) malloc(sizeof(unsigned int) * numeroPesos);
        srand(time(NULL));
        for(i = 0; i < tabela->numeroPesos; i++)
            tabela->vetorPesos[i] = (unsigned int) rand();

        return tabela;
    }
    return NULL;
}/*THashDupla criarTHashDupla(unsigned int m, unsigned int numeroPesos)*/

/*Calcula e retorna a posi��o que a chave deve ocupar na tabela.*/
unsigned int hashTDuplo(THashDupla tabela, tipoChave chave){
    unsigned int tamanho, i, soma = 0;

    /*Tamanho recebe o tamanho da chave a ser inserida.*/
    tamanho = strlen(chave);

    for(i = 0; i < tamanho; i++)
        soma += chave[i] * tabela->vetorPesos[i];

    return soma % tabela->M;
}/*unsigned int hashTDuplo(THashDupla tabela, tipoChave chave)*/

/*Calcula o inclemente que ser� usado caso hava colis�es.*/
unsigned int hashAuxiliar(THashDupla tabela, unsigned int chave){
    return 1 + (chave % (tabela->M - 1));
}

/*Insere um elemento na tabela caso este j� n�o esteja cadastrado. Retorna 1 se a
  inser��o for realizada com sucesso e 0 caso n�o seja poss�vel inserir.*/
int inserirItemTHashDupla(THashDupla tabela, cedulaEleitoral cedula){
    unsigned int posicao, i = 1, incremento;

    /*A vari�vel posicao recebe a posi��o de inser��o.*/
    posicao = hashTDuplo(tabela, cedula.tituloEleitor);

    /*A vari�vel inclemento recebe o valor de inclemente de posi��es que ser� usado caso
      haja colis�es.*/
    incremento = hashAuxiliar(tabela, posicao);

    while(i <= tabela->M && tabela->campoDeControle[posicao]){
        if(!strcmp(tabela->cedula[posicao].tituloEleitor,cedula.tituloEleitor))
            return 0;
        posicao = (posicao + incremento) % tabela->M;
        i++;
    }

    /*Caso i sai do loop while com o seu valor maior que o tamanho da tabela, significa que todas as
      posi��es da tabela foram percorridas e n�o h� posi��es dispon�veis para inser��o.*/
    if(i > tabela->M) return 0;

    /*Insere o elemento na posi��o v�lida, inicializa o campo de controle com 1 para sinalizar
      qua a posi��o est� ocupada, aumenta o quantidadeDados da tabela e retorna 1.*/
    tabela->cedula[posicao] = cedula;
    tabela->campoDeControle[posicao] = 1;
    tabela->quantidadeDados++;
    return 1;
}/*int inserirItemTHashDupla(THashDupla tabela, cedulaEleitoral cedula)*/

/*Atualiza um elemento na tabela caso este seja localizado atrav�s de sua chave. Retorna
  1 caso a atualiza��o seja bem sucedida e 0 caso n�o seja poss�vel atualizar.*/
int atualizarItemTHashDupla(THashDupla tabela, tipoChave chave, cedulaEleitoral cedula){
    unsigned int incremento, i = 1, posicao;
    if(tabela->quantidadeDados == 0) return 0;

    /*Recebe a poss�vel posi��o retornada para a chave atrav�s da fun��o de hash e seu respectivo
      incremento que sera usado para procurar a chave na tabela.*/
    posicao = hashTDuplo(tabela,chave);
    incremento = hashAuxiliar(tabela,posicao);

    /*Caso o elemento n�o esteja na posi��o indicada, realiza uma busca na tabela.*/
    while(i <= tabela->M){
        if(!strcmp(tabela->cedula[posicao].tituloEleitor, chave) && tabela->campoDeControle[posicao])
        {
            tabela->cedula[posicao] = cedula;
            return 1;
        }
        posicao = (posicao + incremento) % tabela->M;
        i++;
    }
    return 0;
}/*int atualizarItemTHashDupla(THashDupla tabela, tipoChave chave, cedulaEleitoral cedula)*/

/*Pesquisa um elemento na tabela pela sua chave, caso encontre, retorna o valor por refer�ncia
  e retorna 1 sinalizando que a busca foi bem sucedida, caso n�o encontre, retorna 0.*/
int pesquisarItemTHashDupla(THashDupla tabela, tipoChave chave, cedulaEleitoral *cedula){
    int posicao, i = 1, incremento;

    if(tabela->quantidadeDados == 0) return 0;

    /*Verifica na posi��o retornada para a chave atrav�s da fun��o de hash se o elemento � igual
      a chave de busca.*/
    posicao = hashTDuplo(tabela,chave);
    incremento = hashAuxiliar(tabela, posicao);

    /*Caso o elemento n�o esteja na posi��o indicada, realiza uma busca na tabela.*/
    while(i <= tabela->M){
        if(!strcmp(tabela->cedula[posicao].tituloEleitor, chave) && tabela->campoDeControle[posicao])
        {
            (*cedula) = tabela->cedula[posicao];
            return 1;
        }
        posicao = (posicao + incremento) % tabela->M;
        i++;
    }
    return 0;
}/*int pesquisarItemTHashDupla(THashDupla tabela, tipoChave chave, cedulaEleitoral *cedula)*/

/*Remove um elemento na tabela atrav�s de sua chave. Caso encontre, retorna o seu conte�do
  por refer�ncia, apaga o elemento e retorna 1 para avisar que a exclus�o foi bem sucedida.
  Caso n�o encontre o elemento, retorna 0.*/
int removerItemTHashDupla(THashDupla tabela, tipoChave chave, cedulaEleitoral *cedula){
    int posicao, i = 1, incremento;

    if(tabela->quantidadeDados == 0) return 0;

    posicao = hashTDuplo(tabela, chave);
    incremento = hashAuxiliar(tabela,posicao);

    /*Caso o elemento n�o esteja na posi��o indicada, realiza uma busca na tabela.*/
     while(i <= tabela->M){
        if(!strcmp(tabela->cedula[posicao].tituloEleitor, chave) && tabela->campoDeControle[posicao])
        {
            (*cedula) = tabela->cedula[posicao];
            tabela->campoDeControle[posicao] = 0;
            tabela->quantidadeDados--;
            return 1;
        }
        posicao = (posicao + incremento) % tabela->M;
        i++;
    }
    return 0;
}/*int removerItemTHashDupla(THashDupla tabela, tipoChave chave, cedulaEleitoral *cedula)*/

/*Libera a mem�ria alocada din�micamente para a cria��o da tabela.*/
void terminarTHashDupla(THashDupla tabela){
    free(tabela->vetorPesos);
    free(tabela->campoDeControle);
    free(tabela->cedula);
    free(tabela);
}/*void terminarTHashDupla(THashDupla tabela)*/
