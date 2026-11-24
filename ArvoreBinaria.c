#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" // inclui os prototipos

// Estrutura de no modificada, para conter um caractere e sua respectiva frequencia (necessario para Huffman)
struct NO {
    unsigned char caractere;
    int frequencia;
    struct NO *esq;
    struct NO *dir;
    struct NO *prox;
};

// Libera cada no da arvore recursivamente
void libera_NO(ArvBin no) {
    if (no == NULL) {
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

// Libera os nos que sobraram na lista encadeada caso falte memoria durante a construcao
void libera_lista(ArvBin lista) {
    while (lista != NULL) {
        ArvBin proximo = lista->prox;
        libera_NO(lista);
        lista = proximo;
    }
}

// Cria um novo no da arvore ja preenchendo caractere, frequencia e os filhos
ArvBin criar_no(unsigned char caractere, int frequencia, ArvBin esq, ArvBin dir) {
    ArvBin novo = (ArvBin) malloc(sizeof(struct NO));

    if (novo != NULL) {
        novo->caractere = caractere;
        novo->frequencia = frequencia;
        novo->esq = esq;
        novo->dir = dir;
        novo->prox = NULL;
    }

    return novo;
}

// Libera todos os nos da arvore e faz a raiz apontar para NULL
void libera_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) {
        return;
    }
    if (*raiz == NULL) {
        return;
    }
    libera_NO(*raiz); // libera cada no
    *raiz = NULL;
}

int estaVazia_ArvBin(ArvBin raiz) {
    if (raiz == NULL) {
        return 1;
    }
    return 0;
}

int totalNO_ArvBin(ArvBin raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int totalNO_esq = totalNO_ArvBin(raiz->esq);
    int totalNO_dir = totalNO_ArvBin(raiz->dir);
    return (totalNO_esq + totalNO_dir + 1);
}

int altura_ArvBin(ArvBin raiz) {
    if (raiz == NULL) {
        return 0;
    }
    int alt_esq = altura_ArvBin(raiz->esq);
    int alt_dir = altura_ArvBin(raiz->dir);
    if (alt_esq > alt_dir) {
        return (alt_esq + 1);
    } else {
        return (alt_dir + 1);
    }
}

// Funcao de preOrdem modificada para exibir frequencia ao inves de um inteiro qualquer
void preOrdem_ArvBin(ArvBin raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("%d\n", raiz->frequencia);
    preOrdem_ArvBin(raiz->esq);
    preOrdem_ArvBin(raiz->dir);
}

//============================================================================================
//===================================== Funcoes proprias =====================================
//============================================================================================

// Insere um no na lista encadeada mantendo a ordem crescente de frequencia
void inserir_ordenado(ArvBin *lista, ArvBin novo_no) {
    if (lista == NULL || novo_no == NULL) {
        return;
    }

    // Caso 1: Lista vazia ou novo no tem a menor frequencia (insercao no inicio)
    if (*lista == NULL || (*lista)->frequencia >= novo_no->frequencia) {
        novo_no->prox = *lista;
        *lista = novo_no;
    } else {
        // Casos 2 e 3: Percorre a lista ate achar a posicao correta (meio ou final)
        ArvBin atual = *lista;

        // Avanca enquanto o proximo no nao for nulo e a frequencia do proximo for menor que a do novo
        while (atual->prox != NULL && atual->prox->frequencia < novo_no->frequencia) {
            atual = atual->prox;
        }

        // Encaixa o novo no na posicao encontrada
        novo_no->prox = atual->prox;
        atual->prox = novo_no;
    }
}

// Cria a lista ordenada a partir da tabela de frequencias dos caracteres
ArvBin preencher_lista_ordenada(int frequencias[Tamanho_tabela]) {
    ArvBin lista = NULL;

    for (int i = 0; i < Tamanho_tabela; i++) {
        if (frequencias[i] > 0) {
            ArvBin novo_no = criar_no((unsigned char) i, frequencias[i], NULL, NULL);

            // Se der erro no malloc, libera o que ja tinha sido criado na lista
            if (novo_no == NULL) {
                libera_lista(lista);
                return NULL;
            }

            inserir_ordenado(&lista, novo_no);
        }
    }

    return lista;
}

// Imprime os elementos da lista ordenada (usada para conferencia)
void print_lista_ordenada(ArvBin lista) {
    if (lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    ArvBin atual = lista;

    // Percorre a lista saltando de no em no pelo ponteiro 'prox'
    while (atual != NULL) {
        if (atual->caractere >= 32 && atual->caractere <= 126) {
            printf("Caractere: '%c' | ASCII %d: %d ocorrencias.\n",
                   atual->caractere, atual->caractere, atual->frequencia);
        } else {
            printf("Caractere byte: %d (ASCII nao visivel): %d ocorrencias.\n",
                   atual->caractere, atual->frequencia);
        }

        atual = atual->prox; // Avanca para o proximo no
    }
}

// Monta a arvore de Huffman juntando sempre os dois nos de menor frequencia
ArvBin construir_arvore_huffman(ArvBin lista) {
    if (lista == NULL) {
        return NULL;
    }

    while (lista->prox != NULL) {
        // 1. Remove os dois primeiros nos (os de menor frequencia)
        ArvBin esquerdo = lista;
        ArvBin direito = lista->prox;

        // Avanca a cabeca da lista para o terceiro elemento
        lista = direito->prox;

        // Limpa os ponteiros 'prox' dos nos removidos
        esquerdo->prox = NULL;
        direito->prox = NULL;

        // 2. Cria o novo no interno (pai) com a soma das frequencias
        int soma_freq = esquerdo->frequencia + direito->frequencia;
        ArvBin pai = criar_no('+', soma_freq, esquerdo, direito);
        if (pai == NULL) {
            libera_NO(esquerdo);
            libera_NO(direito);
            libera_lista(lista);
            return NULL;
        }

        // 3. Reinsere o no pai na lista encadeada, mantendo a ordem
        inserir_ordenado(&lista, pai);
    }

    return lista;
}

// Funcoes criadas para navegar pela arvore sem acessar a struct diretamente
int obter_caractere(ArvBin no) {
    if (no == NULL) {
        return -1;
    }
    return no->caractere;
}

ArvBin obter_esquerda(ArvBin no) {
    if (no == NULL) {
        return NULL;
    }
    return no->esq;
}

ArvBin obter_direita(ArvBin no) {
    if (no == NULL) {
        return NULL;
    }
    return no->dir;
}

int eh_folha(ArvBin no) {
    if (no == NULL) {
        return 0;
    }
    if (no->esq == NULL && no->dir == NULL) {
        return 1;
    }
    return 0;
}

int obter_frequencia(ArvBin no) {
    if (no == NULL) {
        return 0;
    }
    return no->frequencia;
}
