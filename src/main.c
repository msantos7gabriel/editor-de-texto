#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>

#include "../include/arquivos.h"
#include "../include/funcionalidades.h"

InfoArquivos infoarq = {NULL, 0, 0};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    if (argc != 2)
    {
        fprintf(stderr, "Erro: Número incorreto de argumentos.\n");
        fprintf(stderr, "Uso: %s <caminho_do_arquivo>\n", argv[0]);
        return EXIT_FAILURE;
    }

    ncurses_start();

    infoarq.arquivo = carregar_arquivo(argv[1], &infoarq.quantidade_linhas);

    if (infoarq.arquivo == NULL)
    {

        endwin();
        fprintf(stderr, "Erro fatal ao abrir o arquivo.\n");
        return EXIT_FAILURE;
    }

    int opcao;
    int max_y, max_x;

    do
    {

        clear();

        renderizar_tela(infoarq.arquivo, &max_y, &max_x, infoarq.cursor_linha);

        opcao = getch();
        if (opcao != KEY_UP && opcao != KEY_DOWN)
        {
            opcao = tolower(opcao);
        }

        menu(opcao, &infoarq.arquivo, &infoarq.quantidade_linhas, argv[1], &infoarq.cursor_linha);

    } while ((char)opcao != 'q');

    endwin();

    return EXIT_SUCCESS;
}