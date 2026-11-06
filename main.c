#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main(){
	int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

	ArvBin* raiz = cria_ArvBin();
	//ArvBin* raiz;

	if (estaVazia_ArvBin(raiz))
		printf("A arvore binaria esta vazia\n");

	printf("A arvore possui %d nos\n", totalNO_ArvBin(raiz));

	printf("A arvore tem altura %d\n", altura_ArvBin(raiz));

	int i;
	for(i=0; i < N; i++)
		insere_ArvBin(raiz,dados[i]);

    if (consulta_ArvBin(raiz, 20))
        printf("20 esta na arvore\n");
    else
        printf("20 não esta na arvore\n");

    if (remove_ArvBin(raiz, 20)) {
        printf("20 foi excluido\n");
    } else {
        printf("20 não esta na arvore\n");
    }

	printf("A arvore possui %d nos\n", totalNO_ArvBin(raiz));

	printf("A arvore tem altura %d\n", altura_ArvBin(raiz));

	altura_ArvBin(raiz);

	libera_ArvBin(raiz);

	return 0;
}
