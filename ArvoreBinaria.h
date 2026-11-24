#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#ifndef Tamanho_tabela
#define Tamanho_tabela 256
#endif

// Tipo opaco da arvore binaria (a struct NO fica definida apenas no ArvoreBinaria.c)
typedef struct NO* ArvBin;

// Funcoes basicas da arvore
ArvBin criar_no(unsigned char caractere, int frequencia, ArvBin esq, ArvBin dir);
void libera_ArvBin(ArvBin *raiz);
int estaVazia_ArvBin(ArvBin raiz);
int altura_ArvBin(ArvBin raiz);
int totalNO_ArvBin(ArvBin raiz);
void preOrdem_ArvBin(ArvBin raiz);

// Funcoes para a lista ordenada e construcao da arvore de Huffman
void inserir_ordenado(ArvBin *lista, ArvBin novo_no);
ArvBin preencher_lista_ordenada(int frequencias[Tamanho_tabela]);
void print_lista_ordenada(ArvBin lista);
ArvBin construir_arvore_huffman(ArvBin lista);

// Funcoes para acessar os dados do no sem expor a struct
int obter_caractere(ArvBin no);
ArvBin obter_esquerda(ArvBin no);
ArvBin obter_direita(ArvBin no);
int eh_folha(ArvBin no);
int obter_frequencia(ArvBin no);

#endif
