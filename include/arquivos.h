#ifndef ARQUIVOS_H
#define ARQUIVOS_H

int contador_de_linhas(FILE *arquivo);
FILE *carregar_arquivo(char *caminho_do_arquivo, int *qtd_linhas);
void adicionar_linha(FILE *arquivo, int *qtd_linhas);
void deletar_linha(FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

#endif