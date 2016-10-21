#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ControleEleitoral.h"
#include "FuncoesAuxiliares.h"

void votacao(void *tabela, unsigned int tipoDeTabela, THashLinear prefeito, THashLinear vereador,
             FILE *arquivoEntrada, FILE *arquivoSaida){
    int opcao;
    cedulaEleitoral cedula;
    tipoVoto voto;
    cedula.flagPrefeito = 0;
    cedula.flagVereador = 0;

    /*Lê o tipo de voto.*/
    fscanf(arquivoEntrada,"%d",&opcao);

    /*Lê o titulo de eleitor.*/
    fscanf(arquivoEntrada, "%s", cedula.tituloEleitor);

    switch(opcao){
        case 0:
            /*Lê o voto.*/
            fscanf(arquivoEntrada,"%d",&cedula.votoPrefeito);
            cedula.flagPrefeito = 1;

            if(inserirVotoPrefeito(tabela,tipoDeTabela,cedula,prefeito)){
                pesquisarItemTHashLinear(prefeito,cedula.votoPrefeito,&voto);
                fprintf(arquivoSaida,"\nVoto computado, candidato %d possui %d voto(s) - Prefeito\n",
                        voto.numeroCandidato, voto.qtdDeVotosCandidato);
            }
            else
                fprintf(arquivoSaida,"\n%s","Voto não computado.\n");
        break;
        case 1:
            /*Lê o voto.*/
            fscanf(arquivoEntrada,"%d",&cedula.votoVereador);
            cedula.flagVereador = 1;

            if(inserirVotoVereador(tabela,tipoDeTabela,cedula,vereador)){
                pesquisarItemTHashLinear(vereador,cedula.votoVereador,&voto);
                fprintf(arquivoSaida,"\nVoto computado, candidato %d possui %d voto(s) - Vereador\n",
                        voto.numeroCandidato, voto.qtdDeVotosCandidato);
            }
                else
                    fprintf(arquivoSaida,"\n%s","Voto não computado.\n");
        break;
    }
}/*votacao()*/

/*Inicializa a tabela escolhida para ser utilizada no processo eleitoral.*/
void* inicializaTabela(unsigned int tipo, unsigned int tamanho){
    void *tabela;
    switch(tipo){
        case 1: return tabela = (THashDupla) criarTHashDupla(tamanho,TAMANHO_CHAVE);
        case 2: return tabela = (TabelaLista) criarTabelaLista(tamanho,TAMANHO_CHAVE);
        case 3: return tabela = (HashTabelaArvore) criaTabelaHashArvore(tamanho,TAMANHO_CHAVE);
    }
    return NULL;
}

/*Insere um novo voto para prefeito caso o eleitor não tenha votado para esta categoria.*/
int inserirVotoPrefeito(void *tabela, unsigned int tipo, cedulaEleitoral cedula, THashLinear prefeito){
    switch(tipo){
        case 1: if(cadastraVotoPrefeitoTHDupla(tabela,cedula, prefeito)) return 1; return 0;
        case 2: if(cadastraVotoPrefeitoTHLista(tabela,cedula, prefeito)) return 1; return 0;
        case 3: if(cadastraVotoPrefeitoTHArvore(tabela,cedula, prefeito)) return 1; return 0;
    }
    return 0;
}

/*Insere um novo voto para vereador caso o eleitor não tenha votado para esta categoria.*/
int inserirVotoVereador(void *tabela, unsigned int tipo, cedulaEleitoral cedula, THashLinear vereador){
    switch(tipo){
        case 1: if(cadastraVotoVereadorTHDupla(tabela,cedula, vereador)) return 1; return 0;
        case 2: if(cadastraVotoVereadorTHLista(tabela,cedula, vereador)) return 1; return 0;
        case 3: if(cadastraVotoVereadorTHArvore(tabela,cedula, vereador)) return 1; return 0;
    }
    return 0;
}

/*Apura os votos do candidato da categoria selecionada.*/
void apurarVotos(THashLinear prefeito, THashLinear vereador, FILE *arquivoEntrada,FILE * arquivoSaida){
    int opcao, quantidadeCandidatos;

    fscanf(arquivoEntrada,"%d",&opcao);
    fscanf(arquivoEntrada,"%d",&quantidadeCandidatos);
    switch(opcao){
        case 0:
            if(prefeito->quantidadeDeCandidatos > 0) fprintf(arquivoSaida,"\nApurar - Prefeito\n");
            apurarVotosTabela(prefeito,quantidadeCandidatos,arquivoSaida);
        break;
        case 1:
            if(vereador->quantidadeDeCandidatos > 0) fprintf(arquivoSaida,"\nApurar - Vereador\n");
            apurarVotosTabela(vereador,quantidadeCandidatos,arquivoSaida);
        break;
    }
}

/*Remove o eleitor suspeito do cadastro e elimina os votos computados por ele.*/
void removerEleitor(void *tabela, unsigned int tipo, THashLinear prefeito,
                    THashLinear vereador,FILE *arquivoEntrada,FILE * arquivoSaida){
    switch(tipo){
        case 1:
            if(removeEleitorHashDupla(tabela,prefeito,vereador,arquivoEntrada, arquivoSaida)){
                fprintf(arquivoSaida,"\nMeliante removido, %d voto(s) válido(s) no sistema.\n",
                        totalDeVotosNoSistema(prefeito,vereador));
                break;
            }
            fprintf(arquivoSaida,"\nMeliante nao removido, %d voto(s) válido(s) no sistema.\n",
            totalDeVotosNoSistema(prefeito,vereador));
        break;
        case 2:
            if(removeEleitorHashExterno(tabela,prefeito,vereador,arquivoEntrada, arquivoSaida)){
                fprintf(arquivoSaida,"\nMeliante removido, %d voto(s) válido(s) no sistema.\n",
                        totalDeVotosNoSistema(prefeito,vereador));
                break;
            }
            fprintf(arquivoSaida,"\nMeliante nao removido, %d voto(s) válido(s) no sistema.\n",
            totalDeVotosNoSistema(prefeito,vereador));
            break;
        case 3:
            if(removeEleitorHashArvore(tabela,prefeito,vereador,arquivoEntrada, arquivoSaida)){
                fprintf(arquivoSaida,"\nMeliante removido, %d voto(s) válido(s) no sistema.\n",
                        totalDeVotosNoSistema(prefeito,vereador));
                break;
            }
            fprintf(arquivoSaida,"\nMeliante nao removido, %d voto(s) válido(s) no sistema.\n",
            totalDeVotosNoSistema(prefeito,vereador));
            break;
    }
}

/*Verifica a tabela que foi utilizada pelo seu tipo, desaloca o espaço reservado e para as tabelas de prefeito e vereador.*/
void terminaTabelasEleicao(void *tabela, unsigned int tipo, THashLinear prefeito, THashLinear vereador){
    switch(tipo){
        case 1: terminarTHashDupla(tabela); break;
        case 2: terminarTabelaLista(tabela); break;
        case 3: terminaTabelaArvore(tabela); break;
    }
    terminarTHashLinear(prefeito);
    terminarTHashLinear(vereador);
}
