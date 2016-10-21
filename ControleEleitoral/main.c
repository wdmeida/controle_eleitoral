#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //testar tempo
#include "FuncoesAuxiliares.h"
#include "ControleEleitoral.h"

int main()
{
    /*Declara as variáveis que serão utilizadas no programa.*/
    void *tabela;
    THashLinear prefeito, vereador;
    FILE *arquivoSaida, *arquivoEntrada;
    int tipo, tamTabEleitores, tamTabVereador, tamTabPrefeito, operacao;

    /*Abre os arquivo que serão utilizados para leitura e escrita dos dados.*/
    arquivoEntrada = fopen("entrada.txt","r");
    if(!arquivoEntrada) exit(1);
    arquivoSaida = fopen("saida.txt","w");
    if(!arquivoSaida) exit(1);
    /*
    Le as primeiras linhas do arquivo, a primeira equivale ao tipo de estrutura que será utilizada.
    A segunda linha equivale ao tamanho das tabelas que serão criadas.*/
    fscanf(arquivoEntrada,"%d",&tipo);
    fscanf(arquivoEntrada,"%d %d %d",&tamTabVereador,&tamTabPrefeito, &tamTabEleitores);

    /*Calcula o tamanho das tabelas.*/
    tamTabEleitores = calcTamTabela(tamTabEleitores);
    tamTabPrefeito = calcTamTabela(tamTabPrefeito);
    tamTabVereador = calcTamTabela(tamTabVereador);

    /*Inicializa as tabelas.*/
    tabela = inicializaTabela(tipo,tamTabEleitores);
    prefeito = criarTHashLinear(tamTabPrefeito);
    vereador = criarTHashLinear(tamTabVereador);
    do{
        /*Lê a operação que será processada*/
        fscanf(arquivoEntrada,"%d",&operacao);
        setbuf(stdin, NULL);
        switch(operacao){
            case 0: votacao(tabela,tipo,prefeito, vereador,arquivoEntrada,arquivoSaida); break;
            case 1: removerEleitor(tabela,tipo,prefeito,vereador,arquivoEntrada,arquivoSaida); break;
            case 2: apurarVotos(prefeito, vereador, arquivoEntrada, arquivoSaida); break;
        }

    }while(operacao != 3);

    /*Libera a memória alocada para as tabelas.*/
    terminaTabelasEleicao(tabela,tipo,prefeito,vereador);

    /*Fecha os arquivos utilizados.*/
    fclose(arquivoSaida);
    fclose(arquivoEntrada);
    return 0;
}
