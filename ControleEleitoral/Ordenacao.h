#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED
#include"HashLinear.h"

void heapRefaz(tipoVoto *v, int esq, int dir);
void heapConstroi(tipoVoto *v, int n);
void heapSort(tipoVoto *v, int n);
void bubbleSort(tipoVoto *voto, unsigned int quantidade);

#endif
