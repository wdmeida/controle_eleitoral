#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ordenacao.h"

/*O algoritomo heapSort  utilizado para ordenar o vetor com os votos que será usado
  para contabilizar o ranking com os candidatos.*/
void heapRefaz(tipoVoto *v, int esq, int dir)
{
    int i = esq;
    int j = i*2 + 1; /*Primeiro filho de i*/

    tipoVoto aux = v[i]; /*aux = no i (pai de j).*/

    while(j <= dir){
        if(j < dir && v[j].qtdDeVotosCandidato > v[j + 1].qtdDeVotosCandidato)
            j++; /*j recebe o outro filho de i*/
        if(aux.qtdDeVotosCandidato <= v[j].qtdDeVotosCandidato)
            break;
        v[i] = v[j];
        i = j;
        j = i*2 + 1; /*j = primeiro filho de i*/
    }
    v[i] = aux;
}

void heapConstroi(tipoVoto *v, int n)
{
    int esq;
    esq = (n / 2) - 1; /*esq = nó anterior ao primeiro nó folha do heap*/
    while(esq >= 0){
        heapRefaz(v, esq, n-1);
        esq--;
    }
}

void heapSort(tipoVoto *v, int n)
{
    tipoVoto aux;

    heapConstroi(v,n);

    while(n > 1){
        aux = v[n - 1];
        v[n - 1] = v[0];
        v[0] = aux;
        n--;
        heapRefaz(v,0,n - 1); /*Refaz o heap.*/
    }
}

/*O algoritmo bubbleSort é usado para verificar quais os candidatos que possuem a mesma quantidade
  de votos e ordena-los pelo numero do candidato em ordem crescente.*/
void bubbleSort(tipoVoto *voto, unsigned int quantidade){
    int i, j;
    tipoVoto aux;
    for(i = quantidade - 1; i >= 1; i--){
        for(j = 0; j < i; j++){
            if(voto[j].qtdDeVotosCandidato == voto[j+1].qtdDeVotosCandidato)
                if(voto[j].numeroCandidato > voto[j + 1].numeroCandidato){
                    aux = voto[j];
                    voto[j] = voto[j + 1];
                    voto[j + 1] = aux;
                }
        }
    }
}

