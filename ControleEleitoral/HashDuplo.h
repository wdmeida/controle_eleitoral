#ifndef HASHDUPLO_H_INCLUDED
#define HASHDUPLO_H_INCLUDED

#include "CedulaDeEleicao.h"

typedef struct{
    cedulaEleitoral *cedula;
    unsigned int M,
                 quantidadeDados,
                 numeroPesos,
                 *vetorPesos,
                 *campoDeControle;
}tipoHashDuplo;

typedef tipoHashDuplo *THashDupla;

THashDupla criarTHashDupla(unsigned int, unsigned int);
int inserirItemTHashDupla(THashDupla, cedulaEleitoral);
int pesquisarItemTHashDupla(THashDupla, tipoChave, cedulaEleitoral*);
int atualizarItemTHashDupla(THashDupla, tipoChave, cedulaEleitoral);
int removerItemTHashDupla(THashDupla, tipoChave, cedulaEleitoral*);
void terminarTHashDupla(THashDupla);

#endif
