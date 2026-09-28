#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // Inclui funções de manipulação de caracteres, como o tolower()
#include "../include/arquivos.h"
#include "../include/funcionalidades.h"

// Variáveis globais para guardar o ponteiro do arquivo e a quantidade de linhas.
FILE *arquivo = NULL;
int quantidade_linhas;

/*
 * Função: main
 * Objetivo: Ponto de partida do programa.
 * Parâmetros:
 * - int argc: (Argument Count) Conta quantos argumentos foram passados no terminal.
 * - char *argv[]: (Argument Vector) Um array de strings que guarda os argumentos digitados.
 *   > argv[0] é SEMPRE o nome do próprio programa (ex: "./egg")
 *   > argv[1] é o primeiro argumento passado (ex: "teste.txt")
 */
int main(int argc, char *argv[])
{
    // Verifica se o usuário rodou o programa da forma certa.
    // Precisamos de exatamente 2 argumentos: "./egg" (argv[0]) e "teste.txt" (argv[1]).
    if (argc != 2)
    {
        // stderr é a saída de erro padrão do console.
        fprintf(stderr, "Erro: Número incorreto de argumentos.\n");
        fprintf(stderr, "Uso: %s <caminho_do_arquivo>\n", argv[0]);
        
        // Encerra o programa avisando ao Sistema Operacional que houve uma falha.
        return EXIT_FAILURE; 
    }
    else
    {
        // Tenta carregar o arquivo usando o caminho passado no terminal (argv[1]).
        // Passamos o endereço de quantidade_linhas (&) para a função atualizar o valor real dela.
        arquivo = carregar_arquivo(argv[1], &quantidade_linhas);
        
        // Se retornar NULL, significa que ocorreu um erro crítico na abertura/criação do arquivo.
        if (arquivo == NULL)
        {
            return EXIT_FAILURE;
        }

        char opção; // Usaremos para guardar a escolha do usuário
        
        // Início do laço de repetição do menu. 
        // O "do-while" garante que o menu apareça pelo menos UMA vez antes de testar a condição.
        do
        {
            printf("\nOpcoes: [I]nserir, [A]pagar, [U]ndo, [C]opiar, [V]Colar, [S]alvar, [Q]Sair\nEscolha: ");
            
            // Lê o primeiro caractere digitado pelo usuário
            scanf("%c", &opção);
            
            // tolower() converte a letra para minúscula. 
            // Assim, se o usuário digitar 'Q' ou 'q', o programa trata da mesma forma.
            opção = tolower(opção);
            
            // Chama a função que fizemos para consumir o 'Enter' (\n) deixado pelo scanf no buffer
            limpar_buffer();

        } 
        /* 
         * CHAMA A FUNÇÃO MENU AQUI E TESTA O RETORNO
         * 
         * PONTO MUITO IMPORTANTE: Passamos '&arquivo' (o endereço de memória do nosso FILE*).
         * Isso transforma o parâmetro em um ponteiro duplo (FILE **) lá dentro da função menu.
         * É isso que permite que a função 'deletar_linha' altere ESTA variável global quando 
         * o arquivo for reaberto, corrigindo assim o problema de 'Double Free'.
         */
        while (menu(opção, &arquivo, &quantidade_linhas, argv[1]) != 'q');
    }
    
    // Se o loop terminou (usuário apertou 'q'), o programa chega aqui e 
    // retorna avisando ao Sistema Operacional que tudo ocorreu bem.
    return EXIT_SUCCESS;
}