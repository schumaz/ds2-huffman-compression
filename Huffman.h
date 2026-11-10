#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "ArvoreBinaria.h"

void gerar_codigos(ArvBin raiz, char *codigo, int nivel);


void armazenar_codigos(ArvBin raiz, char *codigo, int nivel, char codigos[Tamanho_tabela][Tamanho_tabela]);
#endif