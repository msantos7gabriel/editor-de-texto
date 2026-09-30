#ifndef PILHA_H
#define PILHA_H

// --- ESTRUTURA DAS DUAS PILHAS ---
struct NoPilha
{
    char acao;
    char texto[256];
    struct NoPilha *prox;
};

// --- FUNÇÕES DA PILHA (UNDO / REDO) ---
void push(char qual_acao, char *qual_texto);
int pop(char *acao_devolvida, char *texto_devolvido);
void push_redo(char qual_acao, char *qual_texto);
int pop_redo(char *acao_devolvida, char *texto_devolvido);
void limpar_redo();

#endif
