#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
#include "Leitor.h"

int main() {
    int frequencias[Tamanho_tabela];
    char *caminho = "romeo_juliet_repetido_128x.txt";

    if (calcular_frequencia(caminho, frequencias) == 0) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return 1;
    }

    imprimir_frequencia(frequencias);

    return 0;
}
