#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>

int contador_de_linhas(FILE *arquivo);

FILE *carregar_arquivo(char *caminho_do_arquivo, int *qtd_linhas);

void adicionar_linha(FILE *arquivo, int *qtd_linhas);

void deletar_linha(FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

void adicionar_linha_silencioso(FILE *arquivo, int *qtd_linhas, char *texto);

void apagar_ultima_linha_silencioso(FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

// Localiza uma linha específica do arquivo
void ler_linha(FILE *arquivo, int linha_desejada, char *linha);

#endif