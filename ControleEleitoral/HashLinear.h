#ifndef HASHLINEAR_H_INCLUDED
#define HASHLINEAR_H_INCLUDED

#include "CedulaDeEleicao.h"

typedef struct{
    int numeroCandidato,
        qtdDeVotosCandidato;
}tipoVoto;

typedef struct{
    tipoVoto *votos;
    unsigned int M,
                 quantidadeVotos,
                 quantidadeDeCandidatos,
                 *campoDeControle;
}tipoTHashLinear;

typedef tipoTHashLinear *THashLinear;

THashLinear criarTHashLinear(unsigned int);
int inserirItemTHashLinear(THashLinear, tipoVoto);
int atualizarItemTHashLinear(THashLinear tabela, unsigned int numeroCandidato);
int pesquisarItemTHashLinear(THashLinear, unsigned int, tipoVoto*);
int removerItemTHashLinear(THashLinear, unsigned int, tipoVoto*);

void terminarTHashLinear(THashLinear);

#endif
