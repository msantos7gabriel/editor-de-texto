#include <stdio.h>
#include <stdlib.h>
#include "../include/arquivos.h" // Inclui os cabeçalhos das funções de manipulação do arquivo

/*
 * Função: limpar_tela
 * Objetivo: Limpar o console/terminal para manter a interface do menu organizada.
 */
void limpar_tela()
{
    // Chama o comando "clear" do sistema operacional. 
    // Nota: "clear" funciona em Linux e macOS. Se fosse no Windows, seria system("cls").
    system("clear"); 
}

/*
 * Função: limpar_buffer
 * Objetivo: Esvaziar o buffer do teclado (stdin).
 * Por que é necessário: Funções como 'scanf' muitas vezes deixam o "Enter" ('\n') 
 * preso na memória. Se não limparmos, o próximo 'scanf' ou 'fgets' pode ler esse 'Enter'
 * acidentalmente e pular a entrada de dados do usuário.
 */
void limpar_buffer()
{
    int ch;
    // Fica lendo caracteres do teclado um por um até encontrar o 'Enter' (\n)
    // ou o fim do arquivo/leitura (EOF), consumindo assim o "lixo" que ficou para trás.
    do
    {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

/*
 * Função: menu
 * Objetivo: Gerenciar a escolha do usuário e chamar a função correspondente.
 * Parâmetros Importantes:
 * - FILE **arquivo: Um ponteiro duplo. Ele recebe o ENDEREÇO da variável que guarda 
 *                   o arquivo lá na função main(). Isso permite que o menu passe essa
 *                   referência adiante e permita que o arquivo seja reaberto e atualizado.
 */
char menu(char opcao, FILE **arquivo, int *qtd_linhas, char *nome_arquivo)
{
    // Limpa a tela toda vez que o menu for processar uma nova ação
    limpar_tela();
    
    // Analisa qual foi a letra digitada (já convertida para minúscula pela main)
    switch (opcao)
    {
    case 'i': // Inserir
        // Usamos *arquivo (com um asterisco) para "desempacotar" o ponteiro duplo e 
        // passar o FILE* verdadeiro para a função adicionar_linha.
        adicionar_linha(*arquivo, qtd_linhas);
        break;
        
    case 'a': // Apagar
        // Aqui NÃO usamos o asterisco (*). Passamos o ponteiro duplo 'arquivo' diretamente,
        // porque a função 'deletar_linha' precisa dele duplo para poder reabrir o arquivo
        // e atualizar a variável original lá na main.
        deletar_linha(arquivo, qtd_linhas, nome_arquivo);
        break;
        
    case 'u':
        /* Desfazer - A ser implementado */
        break;
        
    case 'c':
        /* Copiar - A ser implementado */
        break;
        
    case 'v':
        /* Colar - A ser implementado */
        break;
        
    case 's': // Salvar
        printf("O Arquivo foi salvo na memoria\n");
        // O fflush força o sistema operacional a pegar tudo o que está no buffer de saída
        // e gravar imediatamente no disco rígido (no arquivo físico).
        // Usamos *arquivo para aplicar a função ao ponteiro FILE* real.
        fflush(*arquivo);
        break;
        
    case 'q': // Sair (Quit)
        printf("\nFechando o Arquivo...");
        
        // Fecha o arquivo verdadeiro com segurança antes de sair do programa.
        // Como atualizamos os ponteiros corretamente no 'deletar_linha', esse fclose
        // vai fechar o arquivo certo e não causará mais o erro de "Double Free".
        fclose(*arquivo);

        printf("\nSaindo do Programa...\n");
        break;

    default: // Caso o usuário digite uma letra que não está mapeada acima
        limpar_tela();
        printf("\nOpção invalida...\nTente Novamente\n");
        break;
    }
    
    // Retorna a opção escolhida para que o do-while na função main saiba se deve
    // continuar (qualquer letra) ou quebrar o loop (se retornar 'q').
    return opcao;
}