#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "FuncoesAuxiliares.h"
#include "HashExternoLista.h"
#include "HashLinear.h"
#include "HashDuplo.h"
#include "Hash_ABP.h"
#include "Ordenacao.h"

/*Calcula e retorna o tamanho da tabela baseado na quantidade de dados a ser
  recebida.*/
unsigned int calcTamTabela(unsigned int qtdDados){
    unsigned int tamanhoTabela;
    tamanhoTabela = procurarNumeroPrimo(qtdDados + (qtdDados * 0.5));
    return tamanhoTabela;
}

/*Procura um n�mero primo maior do que o valor recebido por par�metro. Retorna
  o n�mero primo encontrado.*/
unsigned int procurarNumeroPrimo(unsigned int numero){
    int i, div = 0, aux = numero;

    while(1){
        for(i = 1; i <= aux; i++)
            if(aux % i == 0)
                div++;

        if(div == 2)
            break;
        aux++;
        div = 0;
    }
    return aux;
}

/*Verifica se o titulo � v�lido (foi digitado todo em min�sculo).*/
unsigned int validarTitulo(tipoChave chave){
    tipoChave buffer;
    int i, tamanho;

    tamanho = strlen(chave);
    if(tamanho > 8) return 0;

    for(i = 0; i < tamanho; i++)
        buffer[i] = tolower(chave[i]);

    if(!strcmp(buffer,chave))
        return 1;
    return 0;
}

/*Fun��es Hashing Externo Lista.*/

/*Pesquisa e verifica se o eleitor j� votou pra este cargo, caso tenha votado
  retorna 1, caso n�o tenha, retorna 0.*/
unsigned int pesquisarVotoVereadorTHLista(TabelaLista tabela, tipoChave chave){
    cedulaEleitoral cedula;
    if(pesquisarItemTabelaLista(tabela,chave,&cedula))
    {
        if(cedula.flagVereador == 1)
            return 1;
    }
    return 0;
}

/*Pesquisa e verifica se o eleitor j� votou pra este cargo, caso tenha votado
  retorna 1, caso n�o tenha, retorna 0.*/
unsigned int pesquisarVotoPrefeitoTHLista(TabelaLista tabela, tipoChave chave){
    cedulaEleitoral cedula;
    if(pesquisarItemTabelaLista(tabela,chave,&cedula))
    {
        if(cedula.flagPrefeito == 1)
            return 1;
    }
    return 0;
}

/*Recebe os voto e verifica se o eleitor j� tenha votado pra o candidato, caso tenha
  retorna 0. Se o eleitor n�o tiver votado, computa o voto e retorna 1. A fun��o recebe
  como par�metros, a tabela que armazen�ra os titulos dos eleitores e seus respectivos
  votos, a cedula contendo seu titulo e seu voto e a tabela na qual
  serao armazenados os votos.*/
unsigned int cadastraVotoPrefeitoTHLista(TabelaLista tabela, cedulaEleitoral cedula, THashLinear prefeito){
    tipoVoto voto, pesquisar;
    cedulaEleitoral auxiliar;

    /*Verifico se o titulo j� votou para est� categoria.*/
    if(pesquisarVotoPrefeitoTHLista(tabela,cedula.tituloEleitor)) return 0;

    /*Atribui o valor para o tipoVoto que guardar� as informa��es para apura��o..*/
    voto.numeroCandidato = cedula.votoPrefeito;
    voto.qtdDeVotosCandidato = 1;
    cedula.flagPrefeito = 1; /*Sinaliza que o candidato possui um voto.*/

    /*Verificar se o eleitor j� est� cadastrado (Se votou em outra categoria). Caso
      j� esteja cadastrado ele altera apenas inserindo o novo voto na categoria.*/
    if(pesquisarItemTabelaLista(tabela, cedula.tituloEleitor,&auxiliar)){
        auxiliar.flagPrefeito = 1;
        auxiliar.votoPrefeito = cedula.votoPrefeito;
        atualizarItemTabelaLista(tabela, cedula.tituloEleitor,auxiliar);
    }
    else
         inserirItemTabelaLista(tabela,cedula);

    /*Cadastra o voto. Caso ocorra algum erro, retorna 0.*/
    if(pesquisarItemTHashLinear(prefeito, voto.numeroCandidato,&pesquisar))
        atualizarItemTHashLinear(prefeito,voto.numeroCandidato);
    else
        inserirItemTHashLinear(prefeito,voto);
    return 1;
}

/*Recebe os voto e verifica se o eleitor j� tenha votado pra o candidato, caso tenha
  retorna 0. Se o eleitor n�o tiver votado, computa o voto e retorna 1. A fun��o recebe
  como par�metros, a tabela que armazen�ra os titulos dos eleitores e seus respectivos
  votos, a cedula contendo seu titulo e seu voto e a tabela na qual
  serao armazenados os votos.*/
unsigned int cadastraVotoVereadorTHLista(TabelaLista tabela, cedulaEleitoral cedula, THashLinear vereador){
    tipoVoto voto, pesquisar;
    cedulaEleitoral auxiliar;

    /*Verifico se o titulo j� votou para est� categoria.*/
    if(pesquisarVotoVereadorTHLista(tabela,cedula.tituloEleitor)) return 0;

    /*Atribui o valor para o tipoVoto que guardar� as informa��es para apura��o..*/
    voto.numeroCandidato = cedula.votoVereador;
    voto.qtdDeVotosCandidato = 1;
    cedula.flagVereador = 1; /*Sinaliza que o candidato possui votos.*/

    /*Verificar se o eleitor j� est� cadastrado (Se votou em outra categoria). Caso
      j� esteja cadastrado ele altera apenas inserindo o novo voto na categoria.*/
    if(pesquisarItemTabelaLista(tabela, cedula.tituloEleitor,&auxiliar)){
        auxiliar.flagVereador = 1;
        auxiliar.votoVereador = cedula.votoVereador;
        atualizarItemTabelaLista(tabela, cedula.tituloEleitor,auxiliar);
    }
    else
         inserirItemTabelaLista(tabela,cedula);

    /*Cadastra o voto. Caso ocorra algum erro, retorna 0.*/
    if(pesquisarItemTHashLinear(vereador,voto.numeroCandidato,&pesquisar))
        atualizarItemTHashLinear(vereador,voto.numeroCandidato);
    else
        inserirItemTHashLinear(vereador,voto);
    return 1;
}

/*Fun��es Hashing Externo �rvore bin�ria de busca.*/

/*Pesquisa e verifica se o eleitor j� votou pra este cargo, caso tenha votado
  retorna 1, caso n�o tenha, retorna 0.*/
unsigned int pesquisarVotoVereadorTHArvore(HashTabelaArvore tabela, tipoChave chave){
    cedulaEleitoral cedula;
    if(pesquisaItemTabelaArvore(tabela,chave,&cedula))
    {
        if(cedula.flagVereador == 1)
            return 1;
    }
    return 0;
}

/*Pesquisa e verifica se o eleitor j� votou pra este cargo, caso tenha votado
  retorna 1, caso n�o tenha, retorna 0.*/
unsigned int pesquisarVotoPrefeitoTHArvore(HashTabelaArvore tabela, tipoChave chave){
    cedulaEleitoral cedula;
    if(pesquisaItemTabelaArvore(tabela,chave,&cedula))
    {
        if(cedula.flagPrefeito == 1)
            return 1;
    }
    return 0;
}

/*Recebe os voto e verifica se o eleitor j� tenha votado pra o candidato, caso tenha
  retorna 0. Se o eleitor n�o tiver votado, computa o voto e retorna 1. A fun��o recebe
  como par�metros, a tabela que armazen�ra os titulos dos eleitores e seus respectivos
  votos, a cedula contendo seu titulo e seu voto e a tabela na qual
  serao armazenados os votos.*/
unsigned int cadastraVotoPrefeitoTHArvore(HashTabelaArvore tabela, cedulaEleitoral cedula, THashLinear prefeito){
    tipoVoto voto, pesquisar;
    cedulaEleitoral auxiliar;

    /*Verifico se o titulo j� votou para est� categoria.*/
    if(pesquisarVotoPrefeitoTHArvore(tabela,cedula.tituloEleitor)) return 0;

    /*Atribui o valor para o tipoVoto que guardar� as informa��es para apura��o..*/
    voto.numeroCandidato = cedula.votoPrefeito;
    voto.qtdDeVotosCandidato = 1;
    cedula.flagPrefeito = 1; /*Sinaliza que o candidato possui um voto.*/

    /*Verificar se o eleitor j� est� cadastrado (Se votou em outra categoria). Caso
      j� esteja cadastrado ele altera apenas inserindo o novo voto na categoria.*/
    if(pesquisaItemTabelaArvore(tabela, cedula.tituloEleitor,&auxiliar)){
        auxiliar.flagPrefeito = 1;
        auxiliar.votoPrefeito = cedula.votoPrefeito;
        insereItemTabelaArvore(tabela, auxiliar);
    }
    else
         insereItemTabelaArvore(tabela,cedula);

    /*Cadastra o voto. Caso ocorra algum erro, retorna 0.*/
    if(pesquisarItemTHashLinear(prefeito, voto.numeroCandidato,&pesquisar))
        atualizarItemTHashLinear(prefeito,voto.numeroCandidato);
    else
        inserirItemTHashLinear(prefeito,voto);

    return 1;
}

/*Recebe os voto e verifica se o eleitor j� tenha votado pra o candidato, caso tenha
  retorna 0. Se o eleitor n�o tiver votado, computa o voto e retorna 1. A fun��o recebe
  como par�metros, a tabela que armazen�ra os titulos dos eleitores e seus respectivos
  votos, a cedula contendo seu titulo e seu voto e a tabela na qual
  serao armazenados os votos.*/
unsigned int cadastraVotoVereadorTHArvore(HashTabelaArvore tabela, cedulaEleitoral cedula, THashLinear vereador){
    tipoVoto voto, pesquisar;
    cedulaEleitoral auxiliar;

    /*Verifico se o titulo j� votou para est� categoria.*/
    if(pesquisarVotoVereadorTHArvore(tabela,cedula.tituloEleitor)) return 0;

    /*Atribui o valor para o tipoVoto que guardar� as informa��es para apura��o..*/
    voto.numeroCandidato = cedula.votoVereador;
    voto.qtdDeVotosCandidato = 1;
    cedula.flagVereador = 1; /*Sinaliza que o candidato possui um voto.*/

    /*Verificar se o eleitor j� est� cadastrado (Se votou em outra categoria). Caso
      j� esteja cadastrado ele altera apenas inserindo o novo voto na categoria.*/
    if(pesquisaItemTabelaArvore(tabela, cedula.tituloEleitor,&auxiliar)){
        auxiliar.flagVereador = 1;
        auxiliar.votoVereador = cedula.votoVereador;
        insereItemTabelaArvore(tabela, auxiliar);
    }
    else
         insereItemTabelaArvore(tabela,cedula);

    /*Cadastra o voto. Caso ocorra algum erro, retorna 0.*/
    if(pesquisarItemTHashLinear(vereador,voto.numeroCandidato,&pesquisar))
        atualizarItemTHashLinear(vereador,voto.numeroCandidato);
    else
        inserirItemTHashLinear(vereador,voto);

    return 1;
}

/*Fun��es Hashing Linear Duplo.*/

/*Pesquisa e verifica se o eleitor j� votou pra este cargo, caso tenha votado
  retorna 1, caso n�o tenha, retorna 0.*/
unsigned int pesquisarVotoVereadorTHDupla(THashDupla tabela, tipoChave chave){
    cedulaEleitoral cedula;
    if(pesquisarItemTHashDupla(tabela,chave,&cedula))
    {
        if(cedula.flagVereador == 1)
            return 1;
    }
    return 0;
}

/*Pesquisa e verifica se o eleitor j� votou pra este cargo, caso tenha votado
  retorna 1, caso n�o tenha, retorna 0.*/
unsigned int pesquisarVotoPrefeitoTHDupla(THashDupla tabela, tipoChave chave){
    cedulaEleitoral cedula;
    if(pesquisarItemTHashDupla(tabela,chave,&cedula))
    {
        if(cedula.flagPrefeito == 1)
            return 1;
    }
    return 0;
}

/*Recebe os voto e verifica se o eleitor j� tenha votado pra o candidato, caso tenha
  retorna 0. Se o eleitor n�o tiver votado, computa o voto e retorna 1. A fun��o recebe
  como par�metros, a tabela que armazen�ra os titulos dos eleitores e seus respectivos
  votos, a cedula contendo seu titulo e seu voto e a tabela na qual
  serao armazenados os votos.*/
unsigned int cadastraVotoPrefeitoTHDupla(THashDupla tabela, cedulaEleitoral cedula, THashLinear prefeito){
    tipoVoto voto, pesquisar;
    cedulaEleitoral auxiliar;

    /*Verifico se o titulo j� votou para est� categoria.*/
    if(pesquisarVotoPrefeitoTHDupla(tabela,cedula.tituloEleitor)) return 0;

    /*Atribui o valor para o tipoVoto que guardar� as informa��es para apura��o..*/
    voto.numeroCandidato = cedula.votoPrefeito;
    voto.qtdDeVotosCandidato = 1;
    cedula.flagPrefeito = 1; /*Sinaliza que o candidato possui um voto.*/

    /*Verificar se o eleitor j� est� cadastrado (Se votou em outra categoria). Caso
      j� esteja cadastrado ele altera apenas inserindo o novo voto na categoria.*/
    if(pesquisarItemTHashDupla(tabela, cedula.tituloEleitor,&auxiliar)){
        auxiliar.flagPrefeito = 1;
        auxiliar.votoPrefeito = cedula.votoPrefeito;
        atualizarItemTHashDupla(tabela, cedula.tituloEleitor,auxiliar);
    }
    else
         inserirItemTHashDupla(tabela,cedula);

     /*Cadastra o voto. Caso ocorra algum erro, retorna 0.*/
    if(pesquisarItemTHashLinear(prefeito, voto.numeroCandidato,&pesquisar))
        atualizarItemTHashLinear(prefeito,voto.numeroCandidato);
    else
        inserirItemTHashLinear(prefeito,voto);

    return 1;
}

/*Recebe os voto e verifica se o eleitor j� tenha votado pra o candidato, caso tenha
  retorna 0. Se o eleitor n�o tiver votado, computa o voto e retorna 1. A fun��o recebe
  como par�metros, a tabela que armazen�ra os titulos dos eleitores e seus respectivos
  votos, a cedula contendo seu titulo e seu voto e a tabela na qual
  serao armazenados os votos.*/
unsigned int cadastraVotoVereadorTHDupla(THashDupla tabela, cedulaEleitoral cedula, THashLinear vereador){
    tipoVoto voto, pesquisar;
    cedulaEleitoral auxiliar;

    /*Verifico se o titulo j� votou para est� categoria.*/
    if(pesquisarVotoVereadorTHDupla(tabela,cedula.tituloEleitor)) return 0;

    /*Atribui o valor para o tipoVoto que guardar� as informa��es para apura��o..*/
    voto.numeroCandidato = cedula.votoVereador;
    voto.qtdDeVotosCandidato = 1;
    cedula.flagVereador = 1; /*Sinaliza que o candidato possui um voto.*/

    /*Verificar se o eleitor j� est� cadastrado (Se votou em outra categoria). Caso
      j� esteja cadastrado ele altera apenas inserindo o novo voto na categoria.*/
    if(pesquisarItemTHashDupla(tabela, cedula.tituloEleitor,&auxiliar)){
        auxiliar.flagVereador = 1;
        auxiliar.votoVereador = cedula.votoVereador;
        atualizarItemTHashDupla(tabela, cedula.tituloEleitor,auxiliar);
    }
    else
         inserirItemTHashDupla(tabela,cedula);

     /*Cadastra o voto. Caso ocorra algum erro, retorna 0.*/
    if(pesquisarItemTHashLinear(vereador,voto.numeroCandidato,&pesquisar))
        atualizarItemTHashLinear(vereador,voto.numeroCandidato);
    else
        inserirItemTHashLinear(vereador,voto);

    return 1;
}

/*Remove os votos dos Eleitor removido.*/
unsigned int retiraVotos(THashLinear prefeito,THashLinear vereador,cedulaEleitoral cedula){
    int votoRemovido = 0;
    tipoVoto votosPrefeito, votosVereador;

    /*Usa a flagPrefeito para verificar se o usuario votou no prefeito.*/
    if(cedula.flagPrefeito == 1)
        /*Remove o voto do eleitor suspeito.*/
        if(removerItemTHashLinear(prefeito,cedula.votoPrefeito,&votosPrefeito))votoRemovido = 1;

    if(cedula.flagVereador == 1)
        /*Remove o voto do eleitor suspeito.*/
       if(removerItemTHashLinear(vereador,cedula.votoVereador,&votosVereador))votoRemovido = 1;
    if(votoRemovido) return 1; return 0;
}

/*Remove o Eleitor do Hash Arvore Binaria e remove os votos*/
unsigned int removeEleitorHashArvore(HashTabelaArvore tabelaArvore,THashLinear prefeito,THashLinear vereador,
                                     FILE* arquivoEntrada, FILE* arquivoSaida){
    cedulaEleitoral cedula;
    tipoChave chave;

    /*Le o titulo de eleitor a ser removido.*/
    fscanf(arquivoEntrada,"%s",chave);
    /*Verifica se o titulo de eleitor est� no Hash*/
    if(removeItemTabelaArvore(tabelaArvore,chave,&cedula)){
        if(retiraVotos(prefeito,vereador,cedula))
            return 1;
    }
    return 0;
}

/*Remove o Eleitor do Hash Duplo e remove os votos*/
unsigned int removeEleitorHashDupla(THashDupla tabelaDupla,THashLinear prefeito,THashLinear vereador,
                                    FILE* arquivoEntrada, FILE* arquivoSaida){
    cedulaEleitoral cedula;
    tipoChave chave;

    /*Le o titulo de eleitor a ser removido.*/
    fscanf(arquivoEntrada,"%s",chave);

    /*Verifica se o titulo de eleitor est� no Hash*/
    if(removerItemTHashDupla(tabelaDupla,chave,&cedula)){
        retiraVotos(prefeito,vereador,cedula);
        return 1;
    }
    return 0;
}

/*Remove o Eleitor do Hash Externo e remove os votos*/
unsigned int removeEleitorHashExterno(TabelaLista tabelaLista,THashLinear prefeito,THashLinear vereador,
                                      FILE* arquivoEntrada, FILE* arquivoSaida){
    cedulaEleitoral cedula;
    tipoChave chave;

    /*Le o titulo de eleitor a ser removido.*/
    fscanf(arquivoEntrada,"%s",chave);

    /*Verifica se o titulo de eleitor est� no Hash*/
    if(removerItemTabelaLista(tabelaLista,chave,&cedula)){
        if(retiraVotos(prefeito,vereador,cedula))
        return 1;
    }
    return 0;
}

/*Retorna o total de votos do sistema.*/
unsigned int totalDeVotosNoSistema(THashLinear prefeito, THashLinear vereador){
    return prefeito->quantidadeVotos + vereador->quantidadeVotos;
}

/*Apura os votos de todos os candidatos. E exibe o numero de candidatos que o usuario informar.
E o ususario informa se deseja apurar os votos do prefeito ou vereador.*/
void apurarVotosTabela(THashLinear tabela, unsigned int quantidade, FILE *arquivoSaida){
    tipoVoto voto[tabela->quantidadeDeCandidatos];

    int i = 0, contador = 0;
    while(i < tabela->M){
        if(tabela->campoDeControle[i]){
            voto[contador] = tabela->votos[i];
            contador++;
        }
        i++;
    }
    heapSort(voto,tabela->quantidadeDeCandidatos);
    bubbleSort(voto,tabela->quantidadeDeCandidatos);

    exibeDadosOrdenados(voto,tabela->quantidadeDeCandidatos,quantidade,arquivoSaida);
}

/*Grava no arquivo a quantidade de candidatos selecionados para serem exibidos de forma ordenada.
  Caso a quantidade pedida para exibi��o seja maior que o tamanho do vetor, imprime o tamanho m�ximo
  deste.*/
void exibeDadosOrdenados(tipoVoto *voto, unsigned int tamanho, unsigned int quantidade, FILE *arquivoSaida){
    int i;
    if(tamanho < quantidade) quantidade = tamanho;
    for(i = 0; i < quantidade; i++)
        fprintf(arquivoSaida,"%d  %d voto(s).\n",voto[i].numeroCandidato,voto[i].qtdDeVotosCandidato);
}
