#include <stdio.h>
#include <string.h>
#include "Huffman.h"

// Percorre a arvore recursivamente montando o codigo de cada folha e guardando na tabela
void preencher_codigos(ArvBin raiz, char *codigo, int nivel, char codigos[Tamanho_tabela][Tamanho_tabela]) {
    if (raiz == NULL) {
        return;
    }

    // Se for folha, encerra a string e salva o codigo na posicao do caractere
    if (eh_folha(raiz)) {
        codigo[nivel] = '\0';

        int caractere = obter_caractere(raiz);
        if (caractere != -1) {
            strcpy(codigos[caractere], codigo);
        }

        return;
    }

    // Quando vai para esquerda ganha um 0
    codigo[nivel] = '0';
    preencher_codigos(obter_esquerda(raiz), codigo, nivel + 1, codigos);

    // Quando vai para direita ganha um 1
    codigo[nivel] = '1';
    preencher_codigos(obter_direita(raiz), codigo, nivel + 1, codigos);
}

// Inicializa a tabela e chama a geracao dos codigos de Huffman
void gerar_tabela_codigos(ArvBin raiz, char codigos[Tamanho_tabela][Tamanho_tabela]) {
    // Limpa a tabela antes de preencher os codigos
    for (int i = 0; i < Tamanho_tabela; i++) {
        codigos[i][0] = '\0';
    }

    if (raiz == NULL) {
        return;
    }

    // Caso o arquivo tenha apenas um tipo de caractere, a raiz ja e folha e recebe o codigo "0"
    if (eh_folha(raiz)) {
        int caractere = obter_caractere(raiz);
        if (caractere != -1) {
            strcpy(codigos[caractere], "0");
        }
        return;
    }

    char codigo[Tamanho_tabela];
    preencher_codigos(raiz, codigo, 0, codigos);
}

// Mostra na tela cada caractere, sua frequencia e o codigo binario gerado
void imprimir_codigos(int frequencias[Tamanho_tabela], char codigos[Tamanho_tabela][Tamanho_tabela]) {
    for (int i = 0; i < Tamanho_tabela; i++) {
        if (codigos[i][0] != '\0') {
            if (i >= 32 && i <= 126) {
                printf("Caractere: '%c' | ASCII %d | Frequencia: %d | Codigo: %s\n",
                       i, i, frequencias[i], codigos[i]);
            } else {
                printf("Caractere byte: %d (ASCII nao visivel) | Frequencia: %d | Codigo: %s\n",
                       i, frequencias[i], codigos[i]);
            }
        }
    }
}

// Le o arquivo original novamente e grava os codigos de Huffman bit a bit no arquivo de saida
int comprimir_arquivo(const char *caminho_entrada, const char *caminho_saida, char codigos[Tamanho_tabela][Tamanho_tabela]) {
    FILE *entrada = fopen(caminho_entrada, "rb");
    if (entrada == NULL) {
        return 0;
    }

    FILE *saida = fopen(caminho_saida, "wb");
    if (saida == NULL) {
        fclose(entrada);
        return 0;
    }

    unsigned char buffer_byte = 0; // Guarda os bits ate completar 1 byte (8 bits)
    int contador_bits = 0;
    int c;

    while ((c = fgetc(entrada)) != EOF) {
        unsigned char caractere = (unsigned char) c;
        char *codigo_atual = codigos[caractere];

        // Percorre cada bit do codigo do caractere lido
        for (int i = 0; codigo_atual[i] != '\0'; i++) {
            // Desloca os bits para a esquerda para abrir espaco para o proximo bit
            buffer_byte = buffer_byte << 1;

            // Se o bit for '1', marca o ultimo bit do buffer como 1
            if (codigo_atual[i] == '1') {
                buffer_byte = buffer_byte | 1;
            }

            contador_bits++;

            // Quando juntar 8 bits, escreve o byte no arquivo e zera o buffer
            if (contador_bits == 8) {
                fwrite(&buffer_byte, sizeof(unsigned char), 1, saida);
                buffer_byte = 0;
                contador_bits = 0;
            }
        }
    }

    // Se sobraram bits sem completar 1 byte no final, desloca completando com zeros e grava
    if (contador_bits > 0) {
        buffer_byte = buffer_byte << (8 - contador_bits);
        fwrite(&buffer_byte, sizeof(unsigned char), 1, saida);
    }

    fclose(entrada);
    fclose(saida);
    return 1;
}
