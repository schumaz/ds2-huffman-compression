#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "ArvoreBinaria.h"

// Gera os codigos binarios a partir da arvore de Huffman e guarda na tabela de codigos
void gerar_tabela_codigos(ArvBin raiz, char codigos[Tamanho_tabela][Tamanho_tabela]);

// Imprime os caracteres encontrados junto com a frequencia e o codigo gerado
void imprimir_codigos(int frequencias[Tamanho_tabela], char codigos[Tamanho_tabela][Tamanho_tabela]);

// Comprime o arquivo de entrada gravando os codigos bit a bit no arquivo de saida
int comprimir_arquivo(const char *caminho_entrada, const char *caminho_saida, char codigos[Tamanho_tabela][Tamanho_tabela]);

#endif
