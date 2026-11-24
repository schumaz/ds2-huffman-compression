#ifndef LEITOR_H
#define LEITOR_H

#ifndef Tamanho_tabela
#define Tamanho_tabela 256
#endif

// Conta a frequencia de cada byte do arquivo (retorna 1 se leu dados, 0 se vazio e -1 se erro ao abrir)
int calcular_frequencia(const char *caminho, int frequencias[Tamanho_tabela]);

// Imprime os caracteres encontrados e suas frequencias (funcao para testes)
void imprimir_frequencia(int frequencias[Tamanho_tabela]);

#endif
