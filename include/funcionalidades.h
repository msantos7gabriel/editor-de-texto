#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H
#include <stdio.h>

void limpar_tela();
void limpar_buffer();
char menu(char opcao, FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

// --- FUNÇÕES DA PILHA (UNDO / REDO) ---
void push(char qual_acao, char* qual_texto);
int pop(char* acao_devolvida, char* texto_devolvido);
void push_redo(char qual_acao, char* qual_texto);
int pop_redo(char* acao_devolvida, char* texto_devolvido);
void limpar_redo();

// --- FUNÇÕES DA FILA (COPIAR / COLAR) ---
void copiar_linha(FILE *arquivo, int qtd_linhas);
void colar_linha(FILE *arquivo, int *qtd_linhas);

#endif