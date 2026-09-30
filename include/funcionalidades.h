#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H
#include <stdio.h>

void limpar_tela();
void limpar_buffer();
char menu(char opcao, FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

// --- FUNÇÕES DA FILA (COPIAR / COLAR) ---
void copiar_linha(FILE *arquivo, int qtd_linhas);
void colar_linha(FILE *arquivo, int *qtd_linhas);

#endif