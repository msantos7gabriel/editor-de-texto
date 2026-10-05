#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "../include/fila.h"

#define TAM_FILA 5
#define MAXIMO_CHAR 80


// Vetor que armazena as linhas copiadas para o clipboard (area de transferencia)
char clipboard[TAM_FILA][MAXIMO_CHAR];

int inicio = 0; // Primeiro elemento da fila
int fim = 0; // Proxima posicao disponivel para inserir uma linha
int qtd = 0; // Quantidade atual de elementos armazenados na fila


// Adiciona uma linha no final da fila
void enqueue(char *linha){

    strcpy(clipboard[fim], linha);
    fim = (fim + 1) % TAM_FILA;
    
    // Se a fila não estiver cheia, aumenta a quantidade de elementos
    if (qtd != TAM_FILA){

        qtd++;

    } else {

        // Se a fila estiver cheia, remove o elemento mais antigo
        inicio = (inicio + 1) % TAM_FILA;

    }
}


// Remove a linha mais antiga da fila e a retorna pelo parâmetro
int dequeue(char *linha){

    if (qtd == 0)
    {
        printw("Não há linhas a serem retiradas.\n");
        return 0;
    } 
    else
    {
        strcpy(linha, clipboard[inicio]);
        inicio = (inicio + 1) % TAM_FILA;
        qtd--;

        return 1;
    }
}

