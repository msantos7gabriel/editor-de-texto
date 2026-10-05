#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Nossas Bibliotecas
#include "../include/arquivos.h"
#include "../include/pilha.h"
#include "../include/fila.h"
#define MAXIMO_CHAR 80

// --- FUNÇÕES DE INTERFACE ---

void ncurses_start()
{
    // Iniciamos o ambiente do ncurses
    initscr();
    cbreak();
    // noecho();
    keypad(stdscr, TRUE);
}

void renderizar_tela(FILE *arquivo, int *max_y, int *max_x, int cursor)
{
    getmaxyx(stdscr, *max_y, *max_x);

    if (*max_y < 16 || *max_x < 80)
    {
        printw("Aviso: O terminal esta muito pequeno!\n");
        printw("Tamanho minimo: 80x16. Tamanho atual: %dx%d\n", *max_x, *max_y);
        printw("\nPor favor, aumente a janela do terminal para continuar...");
        refresh();
        getch();
        return;
    }

    rewind(arquivo);
    char buffer[MAXIMO_CHAR];
    int linha_atual = 0;
    int linha_impressa_na_tela = 0;

    // --- LÊ O ARQUIVO APENAS UMA VEZ DO INÍCIO AO FIM ---
    while (fgets(buffer, MAXIMO_CHAR, arquivo) != NULL)
    {
        // Só imprime se a linha já passou do "scroll" do cursor
        if (linha_atual >= cursor)
        {
            // Proteção da margem do menu inferior
            if (linha_impressa_na_tela >= *max_y - 3)
                break;

            // Imprime e pula para a linha de baixo no monitor
            mvprintw(linha_impressa_na_tela, 0, "%3d | %s", linha_atual + 1, buffer);
            linha_impressa_na_tela++;
        }
        linha_atual++;
    }

    // Menu Inferior
    mvprintw(*max_y - 2, 0, "Opcoes: [I]nserir, [A]pagar, [U]ndo, [R]edo, [C]opiar, [V]Colar, [S]alvar, [Q]Sair");
    mvprintw(*max_y - 1, 0, "Escolha: ");
    refresh();

    // --- FIM DA RENDERIZAÇÃO DO TEXTO ---

    // --- INÍCIO DA RENDERIZAÇÃO DO MENU (Barra Inferior) ---
    // Em vez de usar printw (que joga o texto onde o cursor parou),
    // usamos mvprintw para cravar o menu sempre nas duas últimas linhas da tela.

    mvprintw(*max_y - 2, 0, "Opcoes: [I]nserir, [A]pagar, [U]ndo, [R]edo, [C]opiar, [V]Colar, [S]alvar, [Q]Sair");
    mvprintw(*max_y - 1, 0, "Escolha: ");
    // --- FIM DA RENDERIZAÇÃO DO MENU ---

    // Avisa a placa de vídeo para desenhar tudo
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

// Copia uma linha do arquivo para a fila do clipboard
void copiar_linha(FILE *arquivo, int qtd_linhas)
{
    int linha_desejada;

    printw("\nQuantidade de linhas: %d", qtd_linhas);
    printw("\nQual linha deseja copiar? ");
    scanw("%d", &linha_desejada);
    refresh();

    // Verifica se o número da linha é válido
    if (linha_desejada < 1 || linha_desejada > qtd_linhas)
    {
        printw("Linha inválida.\n");
        return;
    }

    char linha[MAXIMO_CHAR];

    // Lê a linha escolhida do arquivo
    ler_linha(arquivo, linha_desejada, linha);

    // Adiciona a linha à fila do clipboard
    enqueue(linha);

    printw("Linha copiada com sucesso.\n");
}

// Retira uma linha da fila do clipboard e adicional ao final do arquivo
void colar_linha(FILE *arquivo, int *qtd_linhas)
{
    char linha[MAXIMO_CHAR];

    // Tenta retirar a linha mais antiga da fila
    if (dequeue(linha))
    {
        // Adiciona a linha retirada ao arquivo
        adicionar_linha_silencioso(arquivo, qtd_linhas, linha);
        printw("Linha colada com sucesso.\n");
    }
}

// --- MENU ---
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
    { // As chaves aqui resolvem o erro da linha 118

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
        break;
    }

    case 'y':
    case 'r':
    { // Chaves obrigatórias novamente
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
        break;
    }

    case 'c':
        copiar_linha(*arquivo, *qtd_linhas);
        toque_para_continuar();
        break;

    case 'v':
        colar_linha(*arquivo, qtd_linhas);
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