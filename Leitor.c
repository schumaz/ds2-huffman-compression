#include <stdio.h>
#include "Leitor.h"

// Abre o arquivo em modo binario e conta quantas vezes cada caractere aparece
int calcular_frequencia(const char *caminho, int frequencias[Tamanho_tabela]) {
    FILE *arquivo = fopen(caminho, "rb");
    if (arquivo == NULL) {
        return -1;
    }

    // Zera o array de frequencias para garantir integridade
    for (int i = 0; i < Tamanho_tabela; i++) {
        frequencias[i] = 0;
    }

    int c;
    int tem_conteudo = 0;

    // Roda o arquivo, caractere a caractere, e conta suas respectivas frequencias
    while ((c = fgetc(arquivo)) != EOF) {
        unsigned char temp = (unsigned char) c;
        frequencias[temp]++;
        tem_conteudo = 1;
    }

    fclose(arquivo);

    // Retorna 0 se o arquivo estiver vazio, ou 1 se tiver pelo menos um byte
    if (tem_conteudo == 0) {
        return 0;
    }
    return 1;
}

// Imprime o caractere e a frequencia de cada um (funcao para testes)
void imprimir_frequencia(int frequencias[Tamanho_tabela]) {
    for (int i = 0; i < Tamanho_tabela; i++) {
        if (frequencias[i] > 0) {
            if (i >= 32 && i <= 126) {
                printf("Caractere: '%c' | ASCII %d: %d ocorrencias.\n", i, i, frequencias[i]);
            } else {
                printf("Caractere byte: %d (ASCII nao visivel): %d ocorrencias.\n", i, frequencias[i]);
            }
        }
    }
}
