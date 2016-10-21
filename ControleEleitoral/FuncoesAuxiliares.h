#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

/*Define as estruturas básicas que serão usadas pra a manipulação
  e bom funcionamento do processo eleitoral de Alvinópolis City.*/

#include "HashExternoLista.h"
#include "HashLinear.h"
#include "HashDuplo.h"
#include "Hash_ABP.h"
#include "Ordenacao.h"

/*Funções gerais.*/
unsigned int calcTamTabela(unsigned int);
unsigned int procurarNumeroPrimo(unsigned int);

/*Funçoes cadastro Tabela Hashing Linear Duplo.*/
unsigned int cadastraVotoPrefeitoTHDupla(THashDupla, cedulaEleitoral, THashLinear);
unsigned int cadastraVotoVereadorTHDupla(THashDupla, cedulaEleitoral, THashLinear);
unsigned int pesquisarVotoVereadorTHDupla(THashDupla, tipoChave);
unsigned int pesquisarVotoPrefeitoTHDupla(THashDupla, tipoChave);
unsigned int removeEleitorHashDupla(THashDupla,THashLinear ,THashLinear,FILE*,FILE*);

/*Funçoes cadastro Tabela Hashing Externo (Lista).*/
unsigned int cadastraVotoPrefeitoTHLista(TabelaLista, cedulaEleitoral, THashLinear);
unsigned int cadastraVotoVereadorTHLista(TabelaLista, cedulaEleitoral, THashLinear);
unsigned int pesquisarVotoVereadorTHLista(TabelaLista, tipoChave);
unsigned int pesquisarVotoPrefeitoTHLista(TabelaLista, tipoChave);

/*Funçoes cadastro Tabela Hashing Externo (ABB).*/
unsigned int cadastraVotoPrefeitoTHArvore(HashTabelaArvore, cedulaEleitoral, THashLinear);
unsigned int cadastraVotoVereadorTHArvore(HashTabelaArvore, cedulaEleitoral, THashLinear);
unsigned int pesquisarVotoVereadorTHArvore(HashTabelaArvore, tipoChave);
unsigned int pesquisarVotoPrefeitoTHArvore(HashTabelaArvore, tipoChave);
unsigned int removeEleitorHashExterno(TabelaLista,THashLinear ,THashLinear,FILE*,FILE*);
unsigned int removeEleitorHashArvore(HashTabelaArvore,THashLinear ,THashLinear,FILE*,FILE*);

/*Separar depois pelas categorias certas.*/
unsigned int retiraVotos(THashLinear,THashLinear,cedulaEleitoral);
unsigned int totalDeVotosNoSistema(THashLinear,THashLinear);

void apurarVotosTabela(THashLinear tabela, unsigned int quantidade, FILE *arquivoSaida);
void exibeDadosOrdenados(tipoVoto *voto, unsigned int tamanho, unsigned int quantidade, FILE *arquivoSaida);

#endif
