#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#define Tamanho_tabela 256

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
struct NO* insere_no_arvore(unsigned char caractere, int frequencia, struct NO *esq, struct NO *dir);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
void preOrdem_ArvBin(ArvBin *raiz);

void inserir_ordenado(struct NO** lista, struct NO* novo_no);
struct NO* preencher_lista_ordenada(int *frequencias);
void print_lista_ordenada(struct NO* lista);
struct NO* construir_arvore_huffman(struct NO* lista);

#endif
