#include <stdio.h>
#include <stdlib.h>
#include "./arquivos/arquivos.h"

// argc é a contagem de argumentos.
// O nome do programa é sempre o argumento 0.

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Erro: Número incorreto de argumentos.\n");
        fprintf(stderr, "Uso: %s <caminho_do_arquivo>\n", argv[0]);
        return EXIT_FAILURE;
    }
    else
    {
        carregar_arquivo(argv[1]);
    }
}
