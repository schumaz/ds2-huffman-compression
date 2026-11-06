#include <stdio.h>
#include "Leitor.h"

int calcular_frequencia(char *caminho, int *frequencias) {
    FILE *arquivo = fopen(caminho, "r");
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

void impimir_frequencia(int *freuqencias) {

}
