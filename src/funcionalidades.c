#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/arquivos.h"

// --- ESTRUTURA DAS DUAS PILHAS ---
struct NoPilha {
    char acao;
    char texto[256];
    struct NoPilha *prox;
};

static struct NoPilha *topo = NULL;       
static struct NoPilha *topo_redo = NULL;  

// --- FUNÇÕES DA PILHA UNDO ---
void push(char qual_acao, char* qual_texto) {
    struct NoPilha *novo = malloc(sizeof(struct NoPilha));
    if(novo == NULL) return;
    novo->acao = qual_acao;
    strcpy(novo->texto, qual_texto);
    novo->prox = topo;
    topo = novo;
}

int pop(char* acao_devolvida, char* texto_devolvido) {
    if (topo == NULL) return 0; 
    struct NoPilha *temp = topo;
    *acao_devolvida = temp->acao;
    strcpy(texto_devolvido, temp->texto);
    topo = temp->prox;
    free(temp);
    return 1;
}

// --- FUNÇÕES DA PILHA REDO ---
void push_redo(char qual_acao, char* qual_texto) {
    struct NoPilha *novo = malloc(sizeof(struct NoPilha));
    novo->acao = qual_acao;
    strcpy(novo->texto, qual_texto);
    novo->prox = topo_redo;
    topo_redo = novo;
}

int pop_redo(char* acao_devolvida, char* texto_devolvido) {
    if (topo_redo == NULL) return 0; 
    struct NoPilha *temp = topo_redo;
    *acao_devolvida = temp->acao;
    strcpy(texto_devolvido, temp->texto);
    topo_redo = temp->prox;
    free(temp);
    return 1;
}

void limpar_redo() {
    struct NoPilha *temp;
    while (topo_redo != NULL) {
        temp = topo_redo;
        topo_redo = topo_redo->prox;
        free(temp);
    }
}

// --- FUNÇÕES DE INTERFACE ---
void limpar_tela() {
    system("clear"); 
}

void limpar_buffer() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

// --- MENU ---
char menu(char opcao, FILE **arquivo, int *qtd_linhas, char *nome_arquivo)
{
    limpar_tela();
    
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
        
        if (pop(&acao_realizada, texto_salvo)) {
            if (acao_realizada == 'I') {
                printf("-> Undo executado: Apagando a ultima linha inserida...\n");
                apagar_ultima_linha_silencioso(arquivo, qtd_linhas, nome_arquivo);
                push_redo('I', texto_salvo);
            } 
            else if (acao_realizada == 'A') {
                printf("-> Undo executado: Restaurando linha apagada no final do arquivo...\n");
                adicionar_linha_silencioso(*arquivo, qtd_linhas, texto_salvo);
                push_redo('A', texto_salvo);
            }
        } else {
            printf("-> Historico vazio! Nao ha nada para desfazer.\n");
        }
        break;
    }
    
    case 'y': 
    case 'r':
    { // Chaves obrigatórias novamente
        char acao_desfeita;
        char texto_salvo[256];
        
        if (pop_redo(&acao_desfeita, texto_salvo)) {
            if (acao_desfeita == 'I') {
                printf("-> Redo: A refazer a insercao...\n");
                adicionar_linha_silencioso(*arquivo, qtd_linhas, texto_salvo);
                push('I', texto_salvo); 
            } 
            else if (acao_desfeita == 'A') {
                printf("-> Redo: A refazer a exclusao...\n");
                apagar_ultima_linha_silencioso(arquivo, qtd_linhas, nome_arquivo);
                push('A', texto_salvo);
            }
        } else {
            printf("-> Nada para refazer!\n");
        }
        break;
    }
        
    case 'c': break;
    case 'v': break;
        
    case 's': 
        printf("O Arquivo foi salvo na memoria\n");
        fflush(*arquivo);
        break;
        
    case 'q': 
        printf("\nFechando o Arquivo...");
        fclose(*arquivo);
        printf("\nSaindo do Programa...\n");
        break;

    default:
        limpar_tela();
        printf("\nOpção invalida...\nTente Novamente\n");
        break;
    }
    
    return opcao;
}