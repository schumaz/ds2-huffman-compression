#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
#include "Leitor.h"

int main() {
    int frequencias[Tamanho_tabela];
    char *caminho = "bomessebombom.txt";

    if (calcular_frequencia(caminho, frequencias) == 0) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return 1;
    }

    //imprimir_frequencia(frequencias);

    //Lista ordenada dos elementos do texto selecionado, de acordo com sua frequência;
    struct NO* lista_ordenada = preencher_lista_ordenada(frequencias);
    print_lista_ordenada(lista_ordenada);

    return 0;
}
