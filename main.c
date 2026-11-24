#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
#include "Leitor.h"
#include "Huffman.h"

int main(int argc, char *argv[]) {
    int frequencias[Tamanho_tabela];
    const char *caminho = "textoteste.txt";
    const char *caminho_saida = "comprimido.bin";

    // Permite passar o arquivo de entrada e saida pela linha de comando se quiser
    if (argc >= 2) {
        caminho = argv[1];
    }
    if (argc >= 3) {
        caminho_saida = argv[2];
    }

    // Conta a frequencia de cada caractere do arquivo de entrada
    int status_leitura = calcular_frequencia(caminho, frequencias);
    if (status_leitura == -1) {
        printf("Erro ao abrir o arquivo: %s\n", caminho);
        return 1;
    }
    if (status_leitura == 0) {
        printf("O arquivo %s esta vazio, nao ha nada para comprimir.\n", caminho);
        return 0;
    }

    // Lista ordenada dos elementos do texto selecionado, de acordo com sua frequencia
    ArvBin lista_ordenada = preencher_lista_ordenada(frequencias);
    if (estaVazia_ArvBin(lista_ordenada)) {
        printf("Erro ao alocar memoria para a lista ordenada.\n");
        return 1;
    }

    // Criamos a arvore de Huffman a partir da lista ordenada
    ArvBin raiz_huffman = construir_arvore_huffman(lista_ordenada);
    if (estaVazia_ArvBin(raiz_huffman)) {
        printf("Erro ao construir a arvore de Huffman.\n");
        return 1;
    }

    // Gera a tabela de codigos binarios e mostra na tela
    char codigos[Tamanho_tabela][Tamanho_tabela];
    gerar_tabela_codigos(raiz_huffman, codigos);
    imprimir_codigos(frequencias, codigos);

    // Faz a compressao gravando os bits no arquivo binario de saida
    if (comprimir_arquivo(caminho, caminho_saida, codigos)) {
        printf("\nArquivo comprimido gerado com sucesso: %s\n", caminho_saida);
    } else {
        printf("\nErro ao gerar o arquivo comprimido.\n");
        libera_ArvBin(&raiz_huffman);
        return 1;
    }

    libera_ArvBin(&raiz_huffman);
    return 0;
}
