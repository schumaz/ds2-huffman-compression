#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prototipos

// Estrutura de no modificada, para conter um caractere e sua respectiva frequencia (necessario para Huffman)
struct NO{
	unsigned char caractere;
	int frequencia;
	struct NO *esq;
	struct NO *dir;
};

// Funcao de inserir na arvore, modificada para inserir um no e ambos dados (necessarios para Huffman)
struct NO* insere_no_arvore(unsigned char caractere, int frequencia, struct NO *esq, struct NO *dir) {
    struct NO *novo = (struct NO*) malloc(sizeof(struct NO));

    if (novo != NULL) {
        novo->caractere = caractere;
        novo->frequencia = frequencia;
        novo->esq = esq;
        novo->dir = dir;
    }

    return novo;
}

ArvBin* cria_ArvBin(){
	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
	if(raiz != NULL)
		*raiz = NULL;
	return raiz;
}

void libera_NO(struct NO* no){
	if(no == NULL)
		return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	free(no);
	no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
	if(raiz == NULL)
		return;
	libera_NO(*raiz); // libera cada n
	free(raiz); // libera a raiz
}

int estaVazia_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return 1;
	if(*raiz == NULL)
		return 1;
	return 0;
}

int totalNO_ArvBin(ArvBin *raiz){
	if (raiz == NULL)
		return 0;
	if (*raiz == NULL)
		return 0;
	int totalNO_esq = totalNO_ArvBin(&((*raiz)->esq));
	int totalNO_dir = totalNO_ArvBin(&((*raiz)->dir));
	return (totalNO_esq + totalNO_dir + 1);
}

int altura_ArvBin(ArvBin *raiz){
	if (raiz == NULL)
		return 0;
	if (*raiz == NULL)
		return 0;
	int alt_esq = altura_ArvBin(&((*raiz)->esq));
	int alt_dir = altura_ArvBin(&((*raiz)->dir));
	if (alt_esq > alt_dir)
		return (alt_esq + 1);
	else
		return(alt_dir + 1);
}

// Funcao de preOrdem modificada para exibir frequencia ao inves de um inteiro qualquer
void preOrdem_ArvBin(ArvBin *raiz){
	if(raiz == NULL)
		return;
	if(*raiz != NULL){
		printf("%d\n",(*raiz)->frequencia);
		preOrdem_ArvBin(&((*raiz)->esq));
		preOrdem_ArvBin(&((*raiz)->dir));
	}
}
