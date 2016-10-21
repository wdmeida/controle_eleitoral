#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"abp.h"

apontador inicializa_abp(){
    return NULL;
}

int pesquisa_abp(tipoChave chave,cedulaEleitoral* e,apontador p){
    if(p == NULL) return 0;

    if(strcmp(p->info.tituloEleitor,chave) < 0)
        return pesquisa_abp(chave,e,p->esq);
    else
        if(strcmp(p->info.tituloEleitor,chave) > 0)
            return pesquisa_abp(chave,e,p->dir);
        else{
            *e = p->info;
            return 1;
        }

}

int insere_abp(cedulaEleitoral e,apontador* p){
    if((*p) == NULL){/*Atingiu o ponto de inserção*/
        *p = (apontador)malloc(sizeof(TipoNodo));
        (*p)->info = e;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        return 1;
    }
    else
        if(strcmp((*p)->info.tituloEleitor, e.tituloEleitor) > 0)
            return insere_abp(e,&(*p)->dir);
        else
            if(strcmp((*p)->info.tituloEleitor, e.tituloEleitor) < 0)
                return insere_abp(e,&(*p)->esq);
            else{
                int votado = 0;
                if((*p)->info.flagPrefeito == 0){
                   (*p)->info.votoPrefeito = e.votoPrefeito;
                   (*p)->info.flagPrefeito = 1;
                   votado = 1;
                }
                if((*p)->info.flagVereador == 0){
                   (*p)->info.votoVereador = e.votoVereador;
                   (*p)->info.flagVereador = 1;
                   votado = 1;
                }
                if(votado  == 1)
                    return 1;
                else
                    return 0;
        }
}

int retira_abp(tipoChave tituloEleitor, cedulaEleitoral* e,apontador* p){
    apontador a;
    if(*p == NULL)return 0;
    else
       if(strcmp((*p)->info.tituloEleitor,tituloEleitor) < 0)
            return retira_abp(tituloEleitor,e,&(*p)->esq);
        else
            if(strcmp((*p)->info.tituloEleitor,tituloEleitor) > 0)
                return retira_abp(tituloEleitor,e,&(*p)->dir);
            else{
                a = *p;
                *e = (*p)->info;
                /*Verifcando se tem apenas filho a esquerda*/
                if((*p)->dir == NULL)
                    *p = (*p)->esq;
                else
                    if((*p)->esq == NULL)
                        *p = (*p)->dir;
                    else{
                    /*Fazendo p apontar para o
                    filho esquerdo do nodo a ser removido*/
                     p = &(*p)->esq;
                     while((*p)->dir)
                        p = &(*p)->dir;
                     a->info = (*p)->info;
                     a = *p;
                    *p=(*p)->esq;

                    }
             free(a);
             return 1;
            }
}

void percorre_in_ordem(apontador p){
    if(p != NULL){
        percorre_in_ordem(p->esq);
        printf("\n%s",p->info.tituloEleitor);
        percorre_in_ordem(p->dir);
    }
}

void termina_abp(apontador p){
     if(p != NULL){
        termina_abp(p->esq);
        termina_abp(p->dir);
        free(p);
    }
}
