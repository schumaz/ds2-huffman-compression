#include <stdio.h>
#include "Leitor.h"

int calcular_frequencia(char *caminho, int *frequencias) {
    FILE *arquivo = fopen(caminho, "rb");
    if (arquivo == NULL) {
        return  0;
    }

    // Zera o array de frequencias para garantir integridade
    for (int i = 0; i < Tamanho_tabela; i++) {
        frequencias[i] = 0;
    }

    int c;
    // Roda o arquivo de texto, caractere a caractere, e conta suas respectivas frequencias
    while ((c = fgetc(arquivo)) != EOF)  {
        unsigned char temp = (unsigned char) c;
        frequencias[temp]++;
    }

    fclose(arquivo);
    return 1;
}

// Imprime o caractere e a frequencia de cada um (funcao para testes)
void imprimir_frequencia(int *frequencias) {
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
