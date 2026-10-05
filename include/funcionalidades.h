#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

void limpar_tela();
void ncurses_start();
void renderizar_tela(FILE *arquivo, int *max_y, int *max_x, int cursor);
void subir_cursor(int *cursor_posicao, int qtd_linha);
void descer_cursor(int *cursor_posicao);
void toque_para_continuar();
void salvar(FILE *arquivo);
void limpar_buffer();
int menu(int opcao, FILE **arquivo, int *qtd_linhas, char *nome_arquivo, int *cursor_pos);

// --- FUNÇÕES DA FILA (COPIAR / COLAR) ---
void copiar_linha(FILE *arquivo, int qtd_linhas);
void colar_linha(FILE *arquivo, int *qtd_linhas);

#endif