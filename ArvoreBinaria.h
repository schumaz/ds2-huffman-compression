#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
struct NO* insere_no_arvore(unsigned char caractere, int frequencia, struct NO *esq, struct NO *dir);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
void preOrdem_ArvBin(ArvBin *raiz);

#endif
