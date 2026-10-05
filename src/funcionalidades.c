#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "../include/arquivos.h"
#include "../include/pilha.h"
#include "../include/fila.h"
#define MAXIMO_CHAR 80

void ncurses_start()
{

    initscr();
    cbreak();

    keypad(stdscr, TRUE);
}

void renderizar_tela(FILE *arquivo, int *max_y, int *max_x, int cursor)
{
    getmaxyx(stdscr, *max_y, *max_x);

    if (*max_y < 16 || *max_x < 110)
    {
        printw("Aviso: O terminal esta muito pequeno!\n");
        printw("Tamanho minimo: 110x16. Tamanho atual: %dx%d\n", *max_x, *max_y);
        printw("\nPor favor, aumente a janela do terminal para continuar...");
        refresh();
        getch();
        return;
    }

    rewind(arquivo);
    char buffer[MAXIMO_CHAR];
    int linha_atual = 0;
    int linha_impressa_na_tela = 0;

    while (fgets(buffer, MAXIMO_CHAR, arquivo) != NULL)
    {

        if (linha_atual >= cursor)
        {

            if (linha_impressa_na_tela >= *max_y - 3)
                break;

            mvprintw(linha_impressa_na_tela, 0, "%3d | %s", linha_atual + 1, buffer);
            linha_impressa_na_tela++;
        }
        linha_atual++;
    }

    mvprintw(*max_y - 2, 0, "Opcoes: [I]nserir, [A]pagar, [U]ndo, [R]edo, [C]opiar, [V]Colar, [S]alvar, [Q]Sair");
    mvprintw(*max_y - 1, 0, "Escolha: ");
    refresh();

    renderizar_fila_lateral(*max_x);
    mvprintw(*max_y - 2, 0, "Opcoes: [I]nserir, [A]pagar, [U]ndo, [R]edo, [C]opiar, [V]Colar, [S]alvar, [Q]Sair");
    mvprintw(*max_y - 1, 0, "Escolha: ");

    refresh();
}

void subir_cursor(int *cursor_posicao, int qtd_linha)
{
    if (qtd_linha - 1 > *cursor_posicao)
    {
        (*cursor_posicao)++;
    }
}
void descer_cursor(int *cursor_posicao)
{
    if (*cursor_posicao > 0)
    {
        (*cursor_posicao)--;
    }
}

void limpar_tela()
{
    clear();
}

void toque_para_continuar()
{
    printw("\nToque para continuar...");
    refresh();
    getch();
}

void salvar(FILE *arquivo)
{
    printw("\nO Arquivo foi salvo na memoria");
    fflush(arquivo);
    toque_para_continuar();
}

void copiar_linha(FILE *arquivo, int qtd_linhas)
{
    int linha_desejada;

    printw("\nQuantidade de linhas: %d", qtd_linhas);
    printw("\nQual linha deseja copiar? ");
    refresh();
    scanw("%d", &linha_desejada);

    if (linha_desejada < 1 || linha_desejada > qtd_linhas)
    {
        printw("Linha inválida.\n");
        return;
    }

    char linha[MAXIMO_CHAR];

    ler_linha(arquivo, linha_desejada, linha);

    enqueue(linha);

    printw("Linha copiada com sucesso.\n");
}

void colar_linha(FILE *arquivo, int *qtd_linhas)
{
    char linha[MAXIMO_CHAR];

    if (dequeue(linha))
    {

        adicionar_linha_silencioso(arquivo, qtd_linhas, linha);
        printw("Linha colada no final do arquivo com sucesso.\n");
    }
}

int menu(int opcao, FILE **arquivo, int *qtd_linhas, char *nome_arquivo, int *cursor_pos)
{
    limpar_tela();

    if (opcao == KEY_UP)
    {
        descer_cursor(cursor_pos);
        return opcao;
    }
    if (opcao == KEY_DOWN)
    {
        subir_cursor(cursor_pos, *qtd_linhas);
        return opcao;
    }

    switch (opcao)
    {
    case 'i':
        adicionar_linha(*arquivo, qtd_linhas);
        break;

    case 'a':
        deletar_linha(arquivo, qtd_linhas, nome_arquivo);
        break;

    case 'u':
    {

        char acao_realizada;
        char texto_salvo[256];

        if (pop(&acao_realizada, texto_salvo))
        {
            if (acao_realizada == 'I')
            {
                printw("-> Undo executado: Apagando a ultima linha inserida...\n");
                refresh();
                apagar_ultima_linha_silencioso(arquivo, qtd_linhas, nome_arquivo);
                push_redo('I', texto_salvo);
            }
            else if (acao_realizada == 'A')
            {
                printw("-> Undo executado: Restaurando linha apagada no final do arquivo...\n");
                adicionar_linha_silencioso(*arquivo, qtd_linhas, texto_salvo);
                push_redo('A', texto_salvo);
            }
        }
        else
        {
            printw("-> Historico vazio! Nao ha nada para desfazer.\n");
        }
        toque_para_continuar();
        break;
    }

    case 'y':
    case 'r':
    {
        char acao_desfeita;
        char texto_salvo[256];

        if (pop_redo(&acao_desfeita, texto_salvo))
        {
            if (acao_desfeita == 'I')
            {
                printw("-> Redo: A refazer a insercao...\n");
                adicionar_linha_silencioso(*arquivo, qtd_linhas, texto_salvo);
                push('I', texto_salvo);
            }
            else if (acao_desfeita == 'A')
            {
                printw("-> Redo: A refazer a exclusao...\n");
                apagar_ultima_linha_silencioso(arquivo, qtd_linhas, nome_arquivo);
                push('A', texto_salvo);
            }
        }
        else
        {
            printw("-> Nada para refazer!\n");
        }
        toque_para_continuar();
        break;
    }

    case 'c':
        copiar_linha(*arquivo, *qtd_linhas);
        toque_para_continuar();
        break;

    case 'v':
        colar_linha(*arquivo, qtd_linhas);
        toque_para_continuar();
        break;

    case 's':
        salvar(*arquivo);
        break;

    case 'q':
        printw("\nFechando o Arquivo...");
        fclose(*arquivo);
        printw("\nSaindo do Programa...\n");
        toque_para_continuar();
        break;

    default:
        printw("\nOpção invalida...\nTente Novamente\n");
        toque_para_continuar();
        break;
    }

    return opcao;
}