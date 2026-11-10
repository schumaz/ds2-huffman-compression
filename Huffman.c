#include <stdio.h>
#include "Huffman.h"
#include <string.h>

void gerar_codigos(ArvBin raiz, char *codigo, int nivel)
{
    if (raiz == NULL)
    {
        return;
    }

    // Se for folha vai imprimir as informações
    if (eh_folha(raiz))
    {
        codigo[nivel] = '\0';

        printf("caractere: %c - ascii: %d - frequencia: %d - codigo: %s\n",
               obter_caractere(raiz), obter_caractere(raiz), obter_frequencia(raiz), codigo);

        return;
    }

    // Quando vai para esquerda ganha um 0
    codigo[nivel] = '0';
    gerar_codigos(obter_esquerda(raiz), codigo, nivel + 1);
    // Quando vai para direita ganha um 1
    codigo[nivel] = '1';
    gerar_codigos(obter_direita(raiz), codigo, nivel + 1);
}

// A partir daqui iremos guardar os codigos
void armazenar_codigos(ArvBin raiz, char *codigo, int nivel, char codigos[Tamanho_tabela][Tamanho_tabela])
{
    if (raiz == NULL)
    {
        return;
    }

    if (eh_folha(raiz))
    {
        codigo[nivel] = '\0';

        int caractere = obter_caractere(raiz);

        strcpy(codigos[caractere], codigo);

        return;
    }

    codigo[nivel] = '0';

    armazenar_codigos(obter_esquerda(raiz), codigo, nivel + 1, codigos);

    codigo[nivel] = '1';

    armazenar_codigos(obter_direita(raiz), codigo, nivel + 1, codigos);
}