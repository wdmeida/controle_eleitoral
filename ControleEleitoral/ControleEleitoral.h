#ifndef CONTROLEELEITORAL_H_INCLUDED
#define CONTROLEELEITORAL_H_INCLUDED

#include "FuncoesAuxiliares.h"

void votacao(void *tabela, unsigned int tipo, THashLinear prefeito, THashLinear vereador,
             FILE *arquivoEntrada, FILE *arquivoSaida);
void* inicializaTabela(unsigned int tipo, unsigned int tamanho);
void terminaTabelasEleicao(void *tabela, unsigned int tipo, THashLinear prefeito, THashLinear vereador);
void apurarVotos(THashLinear prefeito, THashLinear vereador, FILE *arquivoEntrada,FILE * arquivoSaida);
int inserirVotoPrefeito(void *tabela, unsigned int tipo, cedulaEleitoral cedula, THashLinear prefeito);
int inserirVotoVereador(void *tabela, unsigned int tipo, cedulaEleitoral cedula, THashLinear vereador);
void removerEleitor(void *tabela, unsigned int tipo, THashLinear prefeito,
                    THashLinear vereador,FILE *arquivoEntrada,FILE * arquivoSaida);
#endif
