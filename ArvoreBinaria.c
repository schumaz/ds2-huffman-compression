#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Prototipos

// Estrutura de no modificada, para conter um caractere e sua respectiva frequencia (necessario para Huffman)
struct NO{
	unsigned char caractere;
	int frequencia;
	struct NO *esq;
	struct NO *dir;
	struct NO *prox;
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

void inserir_ordenado(struct NO** lista, struct NO* novo_no) {
	// Caso 1: Lista vazia ou novo nó tem a menor frequência (inserção no início)
	if(*lista==NULL || (*lista)->frequencia >= novo_no->frequencia) {
		novo_no->prox = *lista;
        *lista = novo_no;
	} else {
// Casos 2 e 3: Percorre a lista até achar a posição correta (meio ou final)
        struct NO* atual = *lista;
        
        // Avança enquanto o próximo nó não for nulo E a frequência do próximo for menor que a do novo
        while (atual->prox != NULL && atual->prox->frequencia < novo_no->frequencia) {
            atual = atual->prox;
        }
        
        // Encaixa o novo nó na posição encontrada
        novo_no->prox = atual->prox;
        atual->prox = novo_no;
	}
}

struct NO* preencher_lista_ordenada(int *frequencias) {

	struct NO* lista = NULL; 
    
    for (int i = 0; i < Tamanho_tabela; i++) {
        if (frequencias[i] > 0) {
            struct NO *novo_no = (struct NO*) malloc(sizeof(struct NO));
            novo_no->caractere = (unsigned char) i;
            novo_no->frequencia = frequencias[i];
            novo_no->esq = NULL;
            novo_no->dir = NULL;
            novo_no->prox = NULL;
            
            inserir_ordenado(&lista, novo_no);
        }
    }
    return lista;
}

void print_lista_ordenada(struct NO* lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    struct NO* atual = lista;
    
    // Percorre a lista saltando de nó em nó pelo ponteiro 'prox'
    while (atual != NULL) {
        if (atual->caractere >= 32 && atual->caractere <= 126) {
            printf("Caractere: '%c' | ASCII %d: %d ocorrencias.\n", 
                   atual->caractere, atual->caractere, atual->frequencia);
        } else {
            printf("Caractere byte: %d (ASCII nao visivel): %d ocorrencias.\n", 
                   atual->caractere, atual->frequencia);
        }
        
        atual = atual->prox; // Avança para o próximo nó
    }
}
