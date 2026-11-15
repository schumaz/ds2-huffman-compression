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

int comprimir_arquivo(const char *caminho_entrada, const char *caminho_saida, char codigos[Tamanho_tabela][Tamanho_tabela])
{
    FILE *entrada = fopen(caminho_entrada, "rb");
    if (entrada == NULL) {
        return 0;
    }

    FILE *saida = fopen(caminho_saida, "wb");
    if (saida == NULL) {
        fclose(entrada);
        return 0;
    }

    unsigned char buffer_byte = 0;
    int contador_bits = 0;
    int c;

    while ((c = fgetc(entrada)) != EOF){
        unsigned char caractere = (unsigned char)c;
        char *codigo_atual = codigos[caractere];

        for (int i = 0; codigo_atual[i] != '\0'; i++){
            buffer_byte = buffer_byte << 1;

            if (codigo_atual[i] == '1'){
                buffer_byte = buffer_byte | 1;
            }
            contador_bits++;
            if (contador_bits == 8){
                fwrite(&buffer_byte, sizeof(unsigned char), 1, saida);
                buffer_byte = 0;
                contador_bits = 0;
            }
        }
    }
    
    if (contador_bits > 0){
        buffer_byte = buffer_byte << (8 - contador_bits);
        fwrite(&buffer_byte, sizeof(unsigned char), 1, saida);
    }

    fclose(entrada);
    fclose(saida);
    return 1;
}