#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CedulaDeEleicao.h"
#include "HashLinear.h"

/*Aloca o espaço para a tabela, e inicializa todos os campos.*/
THashLinear criarTHashLinear(unsigned int m){
    THashLinear tabela = (THashLinear) malloc(sizeof(tipoTHashLinear));
    int i;

    if(tabela){
        /*Alocando o espaço das posições da tabela e inicializando contador de votos.*/
        tabela->votos = (tipoVoto*) malloc(sizeof(tipoVoto) * m);
        for(i = 0; i < m; i++)
            tabela->votos[i].qtdDeVotosCandidato = 0;

        /*Inicializando os atributos.*/
        tabela->M = m;
        tabela->quantidadeVotos = 0;
        tabela->quantidadeDeCandidatos = 0;

        /*Aloca espaço e inicializa os campos de controle.*/
        tabela->campoDeControle = (unsigned int*) malloc(sizeof(unsigned int) * m);
        for(i = 0; i < m; i++)
            tabela->campoDeControle[i] = 0;
        return tabela;
    }
    return NULL;
}/*THashLinear criarTHashLinear(unsigned int m)*/

/*Calcula e retorna a posição que a chave deve ocupar na tabela.*/
unsigned int hashLinear(THashLinear tabela, unsigned int chave){
    return chave % tabela->M;
}

/*Insere um elemento na tabela caso este já não esteja cadastrado. Retorna 1 se a
  inserção for realizada com sucesso e 0 caso não seja possível inserir.*/
int inserirItemTHashLinear(THashLinear tabela, tipoVoto voto){
    unsigned int posicao, i = 1;

    /*A variável posicao recebe a posição de inserção.*/
    posicao = hashLinear(tabela, voto.numeroCandidato);

    /*Verifica se o candidato já esta cadastrado, caso esteja, incrementa a quantidade de votos e retorna 1.*/
    while(i <= tabela->M  && tabela->campoDeControle[posicao]){
        if(tabela->votos[posicao].numeroCandidato == voto.numeroCandidato){
            return 0;
        }
        posicao = (posicao + 1) % tabela->M;
        i++;
    }

    /*Caso a variável de controle saia do loop while com o seu valor maior que o tamanho da tabela, todas as
      posições da tabela foram percorridas e não há posições disponíveis para inserção.*/
    if(i > tabela->M) return 0;

    /*Insere o elemento na posição válida caso este já não esteja inserido na tabela. Inicializa o campo de controle
      com 1 para sinalizar qua a posição está ocupada, computa o voto do candidato aumenta o quantidadeDados.*/
    tabela->votos[posicao] = voto;
    tabela->votos[posicao].qtdDeVotosCandidato = 1;
    tabela->campoDeControle[posicao] = 1;
    tabela->quantidadeVotos++;
    tabela->quantidadeDeCandidatos++;
    return 1;
}/*int inserirItemTHashLinear(THashLinear tabela, tipoVoto voto)*/

int atualizarItemTHashLinear(THashLinear tabela, unsigned int numeroCandidato){
    unsigned int i = 1, posicao;
    if(tabela->quantidadeDeCandidatos == 0) return 0;

    /*Recebe a possível posição retornada para a chave através da função de hash e seu respectivo
      incremento que sera usado para procurar a chave na tabela.*/
    posicao = hashLinear(tabela,numeroCandidato);

    /*Caso o elemento não esteja na posição indicada, realiza uma busca na tabela.*/
    while(i <= tabela->M){
        if(tabela->votos[posicao].numeroCandidato == numeroCandidato && tabela->campoDeControle[posicao])
        {
            tabela->votos[posicao].qtdDeVotosCandidato++;
            tabela->quantidadeVotos++;
            return 1;
        }
        posicao = (posicao + 1) % tabela->M;
        i++;
    }
    return 0;
}

/*Pesquisa um elemento na tabela pela sua chave, caso encontre, retorna o valor encontrado
  por referência e retorna 1 sinalizando que a busca foi bem sucedica, caso não encontre, retorna
  0.*/
int pesquisarItemTHashLinear(THashLinear tabela, unsigned int chave, tipoVoto *voto){
    int posicao, i = 1;

    if(tabela->quantidadeDeCandidatos == 0) return 0;

    /*Verifica na posição retornada para a chave através da função de hash se o elemento é igual
      a chave de busca.*/
    posicao = hashLinear(tabela,chave);

    /*Verifica se o candidato já esta cadastrado, caso esteja, aumenta o voto recebido
     e retorna 1 avisando que o voto foi computado com sucesso.*/
    while(i <= tabela->M){
        if(tabela->votos[posicao].numeroCandidato == chave && tabela->campoDeControle[posicao]){
            (*voto) = tabela->votos[posicao];
            return 1;
        }
        posicao = (posicao + 1) % tabela->M;
        i++;
    }
    return 0;
}/*int pesquisarItemTHashLinear(THashLinear tabela, unsigned int chave, tipoVoto *voto)*/

/*Remove um elemento na tabela através de sua chave. Caso encontre, retorna o seu conteúdo
  por referência, apaga o elemento e retorna 1 para avisar que a exclusão foi bem sucedida.
  Caso não encontre o elemento, retorna 0.*/
int removerItemTHashLinear(THashLinear tabela, unsigned int chave, tipoVoto *voto){
    int posicao, i = 1;

    if(tabela->quantidadeDeCandidatos == 0) return 0;

    posicao = hashLinear(tabela, chave);

    /*Verifica se o candidato já esta cadastrado, caso esteja, aumenta o voto recebido
    e retorna 1 avinsando que o voto foi computado com sucesso.*/
    while(i <= tabela->M){
        if(tabela->votos[posicao].numeroCandidato == chave && tabela->campoDeControle[posicao]){
            if(tabela->votos[posicao].qtdDeVotosCandidato > 0)
                tabela->votos[posicao].qtdDeVotosCandidato--;
            tabela->quantidadeVotos--;
            (*voto) = tabela->votos[posicao];
            return 1;
        }
        posicao = (posicao + 1) % tabela->M;
        i++;
    }
    return 0;
}/*int removerItemTHashLinear(THashLinear tabela, unsigned int chave, tipoVoto *voto)*/


/*Libera a memória alocada dinâmicamente para a criação da tabela.*/
void terminarTHashLinear(THashLinear tabela){
    free(tabela->votos);
    free(tabela->campoDeControle);
    free(tabela);
}/*void terminarTHashLinear(THashLinear tabela)*/
