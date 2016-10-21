#ifndef CEDULADEELEICAO_H_INCLUDED
#define CEDULADEELEICAO_H_INCLUDED

#define TAMANHO_CHAVE 9

typedef char tipoChave[TAMANHO_CHAVE];

/*Define os campos da cédula eleitoral utilizada na eleição.*/
typedef struct{
    int votoPrefeito,
        votoVereador,
        flagPrefeito,
        flagVereador;
    tipoChave tituloEleitor;
}cedulaEleitoral;

typedef unsigned int *tipoPesos;

#endif
