#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>

// Nossas Bibliotecas
#include "../include/arquivos.h"
#include "../include/funcionalidades.h"

// Estrutura global
InfoArquivos infoarq = {NULL, 0, 0};

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    // 1. PRIMEIRO: Verificamos os argumentos (antes de abrir qualquer tela)
    if (argc != 2)
    {
        fprintf(stderr, "Erro: Número incorreto de argumentos.\n");
        fprintf(stderr, "Uso: %s <caminho_do_arquivo>\n", argv[0]);
        return EXIT_FAILURE; // Sai do programa na hora
    }

    // Ncurses Start
    ncurses_start();

    // 3. TERCEIRO: Carregamos o arquivo
    infoarq.arquivo = carregar_arquivo(argv[1], &infoarq.quantidade_linhas);

    if (infoarq.arquivo == NULL)
    {
        // MUITO IMPORTANTE: Se der erro, desliga o ncurses antes de fechar o programa!
        endwin();
        fprintf(stderr, "Erro fatal ao abrir o arquivo.\n");
        return EXIT_FAILURE;
    }

    int opcao;
    int max_y, max_x;

    // 4. QUARTO: Loop principal do programa
    do
    {
        // Limpa os rastros da rodada anterior
        clear();

        renderizar_tela(infoarq.arquivo, &max_y, &max_x, infoarq.cursor_linha);

        printw("%i", infoarq.cursor_linha);

        opcao = getch();
        if (opcao != KEY_UP && opcao != KEY_DOWN)
        {
            opcao = tolower(opcao);
        }

        menu(opcao, &infoarq.arquivo, &infoarq.quantidade_linhas, argv[1], &infoarq.cursor_linha);

    } while ((char)opcao != 'q');

    // 5. QUINTO: O usuário pediu para sair, encerramos tudo em segurança
    endwin();

    return EXIT_SUCCESS;
}