#ifndef ARQUIVOS_H
#define ARQUIVOS_H

typedef struct
{
    FILE *arquivo;
    int quantidade_linhas;
    int cursor_linha;
} InfoArquivos;

#define MAXIMO_LINHAS 100
#define MAXIMO_CHAR 80

int contador_de_linhas(FILE *arquivo);

FILE *carregar_arquivo(char *caminho_do_arquivo, int *qtd_linhas);

void adicionar_linha(FILE *arquivo, int *qtd_linhas);

void deletar_linha(FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

void adicionar_linha_silencioso(FILE *arquivo, int *qtd_linhas, char *texto);

void apagar_ultima_linha_silencioso(FILE **arquivo, int *qtd_linhas, char *nome_arquivo);

void ler_linha(FILE *arquivo, int linha_desejada, char *linha);

#endif