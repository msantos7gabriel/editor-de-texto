#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Nossas Bibliotecas
#include "../include/funcionalidades.h"
#include "../include/pilha.h"
#include "../include/arquivos.h"

/*
 * Função: contador_de_linhas
 * Objetivo: Percorrer o arquivo inteiro e contar quantas linhas ele possui.
 * Retorno: A quantidade total de linhas (int).
 */
int contador_de_linhas(FILE *arquivo)
{
    char c[MAXIMO_CHAR];
    int quantidade_linhas = 0;

    // fgets lê uma linha do arquivo e armazena em 'c'.
    // Ele avança o ponteiro de leitura automaticamente.
    // Quando chegar ao final do arquivo, fgets retorna NULL e o loop para.
    while (fgets(c, MAXIMO_CHAR, arquivo) != NULL)
    {
        quantidade_linhas += 1; // A cada linha lida com sucesso, incrementa o contador
    }

    return quantidade_linhas;
}

/*
 * Função: carregar_arquivo
 * Objetivo: Tentar abrir um arquivo existente ou criar um novo se não existir, e contar suas linhas.
 * Retorno: O ponteiro para o arquivo aberto (FILE *).
 */
FILE *carregar_arquivo(char *caminho_do_arquivo, int *qtd_linhas)
{
    FILE *arquivo = NULL;

    // Tenta abrir o arquivo no modo "a+" (leitura e escrita adicionando ao final).
    // Na pagina 356 do livro C: Como Programar tem todos os tipos de modo de abertura.
    if ((arquivo = fopen(caminho_do_arquivo, "a+")) == NULL)
    {
        // Se falhou ao abrir (ex: arquivo não existe), avisa no log de erro
        printw("Não Foi possivel abrir o aquivo para edição\n");
        printw("Tentando Criar arquivo...\n");
        refresh();

        // Tenta criar o arquivo forçadamente usando o modo "w+" (cria para leitura/escrita)
        if ((arquivo = fopen(caminho_do_arquivo, "w+")) == NULL)
        {
            printw("Falha na criação do arquivo\n");
            return NULL; // Se falhou até na criação, encerra a função retornando nulo
            refresh();
        }
        printw("Arquivo Criado\n");
        refresh();
    }

    // Chama a função para contar as linhas e atualiza o valor na variável da função main
    *qtd_linhas = contador_de_linhas(arquivo);

    // O contador de linhas leu o arquivo até o final.
    // O rewind rebobina o ponteiro de volta para o início do arquivo para podermos operá-lo depois.
    rewind(arquivo);

    printw("Acessando Arquivo\n");
    refresh();
    return arquivo; // Retorna o arquivo devidamente aberto e posicionado no início
}

/*
 * Função: adicionar_linha
 * Objetivo: Pedir uma string ao usuário e adicioná-la ao final do arquivo.
 */
void adicionar_linha(FILE *arquivo, int *qtd_linhas)
{
    char linha_nova[MAXIMO_CHAR];

    printw("\nEscreva a nova linha de entrada: ");
    refresh();

    // Pega a entrada digitada pelo usuário no teclado (stdin)
    wgetnstr(stdscr, linha_nova, MAXIMO_CHAR);
    strcat(linha_nova, "\n");

    // --- INÍCIO DA LIGAÇÃO COM A ISSUE 2 ---
    // Agora capturamos o texto real ('linha_nova') no momento exato em que o usuário digita.
    // Guardamos na Pilha com a tag 'I' de Inserção para o Undo saber o que foi feito.
    push('I', linha_nova);

    // Como o usuário fez uma ação nova manualmente, o futuro mudou.
    // Portanto, devemos limpar a Pilha de Redo (Refazer).
    limpar_redo();
    // --- FIM DA LIGAÇÃO ---

    // Escreve a nova linha diretamente no arquivo.
    // Como abrimos em modo "a+", isso sempre será escrito no final.
    fprintf(arquivo, "%s", linha_nova);

    // Atualiza a contagem de linhas geral do programa (variável da main)
    printw("\nLinha adicionada no arquivo");
    refresh();
    *qtd_linhas += 1;
    salvar(arquivo);
    return;
}

/*
 * Função: deletar_linha
 * Objetivo: Apagar uma linha específica do arquivo copiando tudo para um temporário, exceto a linha alvo.
 * Observação: Recebe FILE **arquivo (ponteiro duplo) para poder atualizar o arquivo na função main.
 */
void deletar_linha(FILE **arquivo, int *qtd_linhas, char *nome_arquivo)
{
    // Verificação de segurança: se não há linhas, aborta a função
    if (*qtd_linhas == 0)
    {
        printw("\nNão Há linhas para serem apagadas ");
        return;
    }

    int linha_deletada;
    printw("\nquantidade de linhas: %d", *qtd_linhas);
    printw("\nQual Linha Você deseja deletar ?:");
    scanw("%i", &linha_deletada);
    refresh();

    // Verifica se o usuário pediu para apagar uma linha que não existe
    if (linha_deletada > *qtd_linhas)
    {
        printw("O Valor digitado é Maior que a quantidade de linhas do arquivo\n");
        return;
    }

    char buffer[MAXIMO_CHAR];
    int linha_atual = 1; // Inicia em 1 porque humanos começam a contar do 1 (e não do 0)

    // Cria um arquivo temporário oculto que vai receber as linhas copiadas
    FILE *temp = fopen(".temp.txt", "w+");
    if (temp == NULL)
    {
        printw("\nErro ao criar arquivo temporário.\n");
        return;
    }

    // Usa *arquivo para acessar o ponteiro verdadeiro da main e rebobina ele pro início
    rewind(*arquivo);

    // Percorre linha por linha do arquivo original
    while (fgets(buffer, MAXIMO_CHAR, *arquivo) != NULL)
    {
        // Se a linha atual NÃO for a linha que queremos apagar, copiamos ela para o temp.
        // Se for a linha indesejada, o if é ignorado, ou seja, ela "some".
        if (linha_deletada != linha_atual)
        {
            fprintf(temp, "%s", buffer);
        }
        else
        {
            // --- INÍCIO DA LIGAÇÃO COM A ISSUE 2 ---
            // Se for a linha que vamos apagar, nós a "salvamos" antes dela sumir!
            // Guardamos na Pilha com a tag 'A' (Apagar) e o texto exato ('buffer').
            push('A', buffer);
            limpar_redo(); // Limpa o Redo pois uma nova ação manual foi feita
            // --- FIM DA LIGAÇÃO ---
        }
        linha_atual++; // Passa para a próxima linha
    }

    // Fecha os dois arquivos para liberar o acesso do Sistema Operacional a eles
    fclose(*arquivo);
    fclose(temp);

    // Remove o arquivo antigo (original)
    remove(nome_arquivo);

    // Renomeia o temporário (que já está sem a linha) para o nome do arquivo original
    rename(".temp.txt", nome_arquivo);

    // Atualiza a quantidade de linhas geral, já que apagamos uma
    *qtd_linhas -= 1;

    // REABRE o arquivo recém-criado/renomeado.
    // Como usamos *arquivo, essa reatribuição altera diretamente a variável da main,
    // evitando o erro de liberação dupla (double free).
    *arquivo = fopen(nome_arquivo, "a+");
    printw("\nLinha deletada com sucesso.");

    return;
}

// =========================================================================
// FUNÇÕES SILENCIOSAS PARA O UNDO USAR (Exigência da Issue 2)
// O Undo não pode chamar as funções normais acima, porque elas possuem
// printf/scanf e parariam o programa esperando o usuário digitar algo.
// =========================================================================

/*
 * Função: adicionar_linha_silencioso
 * Objetivo: Inserir texto diretamente no final do arquivo sem interação do usuário (usado pelo Undo/Redo).
 */
void adicionar_linha_silencioso(FILE *arquivo, int *qtd_linhas, char *texto)
{
    fprintf(arquivo, "%s", texto);
    fflush(arquivo);
    *qtd_linhas += 1;
}

/*
 * Função: apagar_ultima_linha_silencioso
 * Objetivo: Remove a última linha do arquivo copiando as demais para um temporário (usado pelo Undo/Redo).
 */
void apagar_ultima_linha_silencioso(FILE **arquivo, int *qtd_linhas, char *nome_arquivo)
{
    if (*qtd_linhas == 0)
        return;

    char buffer[MAXIMO_CHAR];
    int linha_atual = 1;

    // Cria um arquivo temporário para copiar tudo, exceto a última linha
    FILE *temp = fopen(".temp.txt", "w+");
    rewind(*arquivo);

    while (fgets(buffer, MAXIMO_CHAR, *arquivo) != NULL)
    {
        // Se a linha atual não for a última, copia para o arquivo novo
        if (linha_atual != *qtd_linhas)
        {
            fprintf(temp, "%s", buffer);
        }
        linha_atual++;
    }

    // Substitui o arquivo original pelo temporário (que agora tem 1 linha a menos)
    fclose(*arquivo);
    fclose(temp);
    remove(nome_arquivo);
    rename(".temp.txt", nome_arquivo);
    *qtd_linhas -= 1;
    *arquivo = fopen(nome_arquivo, "a+");
}

// Localiza e copia uma linha específica do arquivo
// para a variável recebida pelo parâmetro
void ler_linha(FILE *arquivo, int linha_desejada, char *linha)
{
    char buffer[MAXIMO_CHAR];
    int linha_atual = 1;

    rewind(arquivo);

    while (fgets(buffer, MAXIMO_CHAR, arquivo) != NULL)
    {
        // Verifica se a linha atual é a linha desejada
        if (linha_atual == linha_desejada)
        {
            strcpy(linha, buffer);
            return;
        }
        else
        {
            linha_atual++;
        }
    }
}