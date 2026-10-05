#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "../include/funcionalidades.h"
#include "../include/pilha.h"
#include "../include/arquivos.h"

int contador_de_linhas(FILE *arquivo)
{
    char c[MAXIMO_CHAR];
    int quantidade_linhas = 0;

    while (fgets(c, MAXIMO_CHAR, arquivo) != NULL)
    {
        quantidade_linhas += 1;
    }

    return quantidade_linhas;
}

FILE *carregar_arquivo(char *caminho_do_arquivo, int *qtd_linhas)
{
    FILE *arquivo = NULL;

    if ((arquivo = fopen(caminho_do_arquivo, "a+")) == NULL)
    {

        printw("Não Foi possivel abrir o aquivo para edição\n");
        printw("Tentando Criar arquivo...\n");
        refresh();

        if ((arquivo = fopen(caminho_do_arquivo, "w+")) == NULL)
        {
            printw("Falha na criação do arquivo\n");
            return NULL;
            refresh();
        }
        printw("Arquivo Criado\n");
        refresh();
    }

    *qtd_linhas = contador_de_linhas(arquivo);

    rewind(arquivo);

    printw("Acessando Arquivo\n");
    refresh();
    return arquivo;
}

void adicionar_linha(FILE *arquivo, int *qtd_linhas)
{
    char linha_nova[MAXIMO_CHAR];

    printw("\nEscreva a nova linha de entrada: ");
    refresh();

    wgetnstr(stdscr, linha_nova, MAXIMO_CHAR);
    strcat(linha_nova, "\n");

    push('I', linha_nova);

    limpar_redo();

    fprintf(arquivo, "%s", linha_nova);

    printw("\nLinha adicionada no arquivo");
    refresh();
    *qtd_linhas += 1;
    salvar(arquivo);
    return;
}

void deletar_linha(FILE **arquivo, int *qtd_linhas, char *nome_arquivo)
{

    if (*qtd_linhas == 0)
    {
        printw("\nNão Há linhas para serem apagadas ");
        return;
    }

    int linha_deletada;
    printw("\nquantidade de linhas: %d", *qtd_linhas);
    printw("\nQual Linha Você deseja deletar ?:");
    scanw("%i", &linha_deletada);
    refresh();

    if (linha_deletada > *qtd_linhas)
    {
        printw("O Valor digitado é Maior que a quantidade de linhas do arquivo\n");
        return;
    }

    char buffer[MAXIMO_CHAR];
    int linha_atual = 1;

    FILE *temp = fopen(".temp.txt", "w+");
    if (temp == NULL)
    {
        printw("\nErro ao criar arquivo temporário.\n");
        return;
    }

    rewind(*arquivo);

    while (fgets(buffer, MAXIMO_CHAR, *arquivo) != NULL)
    {

        if (linha_deletada != linha_atual)
        {
            fprintf(temp, "%s", buffer);
        }
        else
        {

            push('A', buffer);
            limpar_redo();
        }
        linha_atual++;
    }

    fclose(*arquivo);
    fclose(temp);

    remove(nome_arquivo);

    rename(".temp.txt", nome_arquivo);

    *qtd_linhas -= 1;

    *arquivo = fopen(nome_arquivo, "a+");
    printw("\nLinha deletada com sucesso.");

    return;
}

void adicionar_linha_silencioso(FILE *arquivo, int *qtd_linhas, char *texto)
{
    fprintf(arquivo, "%s", texto);
    fflush(arquivo);
    *qtd_linhas += 1;
}

void apagar_ultima_linha_silencioso(FILE **arquivo, int *qtd_linhas, char *nome_arquivo)
{
    if (*qtd_linhas == 0)
        return;

    char buffer[MAXIMO_CHAR];
    int linha_atual = 1;

    FILE *temp = fopen(".temp.txt", "w+");
    rewind(*arquivo);

    while (fgets(buffer, MAXIMO_CHAR, *arquivo) != NULL)
    {

        if (linha_atual != *qtd_linhas)
        {
            fprintf(temp, "%s", buffer);
        }
        linha_atual++;
    }

    fclose(*arquivo);
    fclose(temp);
    remove(nome_arquivo);
    rename(".temp.txt", nome_arquivo);
    *qtd_linhas -= 1;
    *arquivo = fopen(nome_arquivo, "a+");
}

void ler_linha(FILE *arquivo, int linha_desejada, char *linha)
{
    char buffer[MAXIMO_CHAR];
    int linha_atual = 1;

    rewind(arquivo);

    while (fgets(buffer, MAXIMO_CHAR, arquivo) != NULL)
    {

        if (linha_atual == linha_desejada)
        {
            strcpy(linha, buffer);
            return;
        }
        else
        {
            linha_atual++;
        }
    }
}