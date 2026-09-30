#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arquivos.h"
#include "../include/fila.h"

// --- ESTRUTURA DAS DUAS PILHAS ---
struct NoPilha
{
    char acao;
    char texto[256];
    struct NoPilha *prox;
};

static struct NoPilha *topo = NULL;
static struct NoPilha *topo_redo = NULL;

// --- FUNÇÕES DA PILHA UNDO ---
void push(char qual_acao, char *qual_texto)
{
    struct NoPilha *novo = malloc(sizeof(struct NoPilha));
    if (novo == NULL)
        return;
    novo->acao = qual_acao;
    strcpy(novo->texto, qual_texto);
    novo->prox = topo;
    topo = novo;
}

int pop(char *acao_devolvida, char *texto_devolvido)
{
    if (topo == NULL)
        return 0;
    struct NoPilha *temp = topo;
    *acao_devolvida = temp->acao;
    strcpy(texto_devolvido, temp->texto);
    topo = temp->prox;
    free(temp);
    return 1;
}

// --- FUNÇÕES DA PILHA REDO ---
void push_redo(char qual_acao, char *qual_texto)
{
    struct NoPilha *novo = malloc(sizeof(struct NoPilha));
    novo->acao = qual_acao;
    strcpy(novo->texto, qual_texto);
    novo->prox = topo_redo;
    topo_redo = novo;
}

int pop_redo(char *acao_devolvida, char *texto_devolvido)
{
    if (topo_redo == NULL)
        return 0;
    struct NoPilha *temp = topo_redo;
    *acao_devolvida = temp->acao;
    strcpy(texto_devolvido, temp->texto);
    topo_redo = temp->prox;
    free(temp);
    return 1;
}

void limpar_redo()
{
    struct NoPilha *temp;
    while (topo_redo != NULL)
    {
        temp = topo_redo;
        topo_redo = topo_redo->prox;
        free(temp);
    }
}
