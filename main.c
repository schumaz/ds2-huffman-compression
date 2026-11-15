#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
#include "Leitor.h"
#include "Huffman.h"

int main()
{
    int frequencias[Tamanho_tabela];
    char *caminho = "textoteste.txt";
    char *caminho_saida = "comprimido.bin";

    if (calcular_frequencia(caminho, frequencias) == 0)
    {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return 1;
    }

    // imprimir_frequencia(frequencias);

    // Lista ordenada dos elementos do texto selecionado, de acordo com sua frequência;
    struct NO *lista_ordenada = preencher_lista_ordenada(frequencias);
    // print_lista_ordenada(lista_ordenada);

    // Criamos a ArvBin
    ArvBin raiz_huffman = construir_arvore_huffman(lista_ordenada);
    preOrdem_ArvBin(&raiz_huffman);

    char codigos[Tamanho_tabela][Tamanho_tabela];
    char codigo[Tamanho_tabela];

    for (int i = 0; i < Tamanho_tabela; i++)
    {
        codigos[i][0] = '\0';
    }

    gerar_codigos(raiz_huffman, codigo, 0);
    armazenar_codigos(raiz_huffman, codigo, 0, codigos);

    printf("Teste se armazenou s: %s\n", codigos[115]);
    printf("Teste se armazenou e: %s\n", codigos[101]);
    printf("Teste se armazenou espaco: %s\n", codigos[32]);

    if (comprimir_arquivo(caminho, caminho_saida, codigos)){
        printf("\nArquivo comprimido gerado com sucesso: %s\n", caminho_saida);
    }
    else{
        printf("\nErro ao gerar o arquivo comprimido.\n");
    }

    libera_ArvBin(&raiz_huffman);
    return 0;
}
