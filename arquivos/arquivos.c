#include <stdio.h>
#include <stdlib.h>

int carregar_arquivo(char *caminho_do_arquivo)
{
    FILE *arquivo = NULL;
    // char linha[256];

    if ((arquivo = fopen(caminho_do_arquivo, "r+")) == NULL)
    {
        fprintf(stderr, "Não Foi possivel abrir o aquivo para edição\n");
        fprintf(stdout, "Tentando Criar arquivo...\n");
        if ((arquivo = fopen(caminho_do_arquivo, "w+")) == NULL)
        {
            fprintf(stderr, "Falha na criação do arquivo\n");
            return EXIT_FAILURE;
        }
        }
    fclose(arquivo);
    return EXIT_SUCCESS;

    // else
    // {
    //     while (fgets(linha, sizeof(linha), arquivo) != NULL)
    //     {
    //         printf("%s", linha);
    //     }
    // }
    // return 0;
}