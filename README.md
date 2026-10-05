# 📝 Editor de Texto em C

Projeto desenvolvido em C para simular um editor de texto em terminal, com foco na aplicação prática de estruturas de dados como pilhas e filas, além de manipulação de arquivos em modo de edição interativa.

<p align="center">
    <a href="https://github.com/msantos7gabriel/editor-de-texto"><img src="https://img.shields.io/badge/C-C11-00599C?style=for-the-badge&logo=c&logoColor=white" alt="Linguagem C C11"></a>
    <a href="https://github.com/msantos7gabriel/editor-de-texto"><img src="https://img.shields.io/badge/GNU%20Make-build-A42E2B?style=for-the-badge&logo=gnu&logoColor=white" alt="GNU Make"></a>
    <a href="https://github.com/msantos7gabriel/editor-de-texto"><img src="https://img.shields.io/badge/Terminal-ncurses-2E8B57?style=for-the-badge" alt="ncurses"></a>
</p>

<p align="center">
    <a href="https://github.com/msantos7gabriel/editor-de-texto"><img src="https://img.shields.io/github/repo-size/msantos7gabriel/editor-de-texto?style=flat-square&logo=github" alt="Tamanho do repositório"></a>
    <a href="https://github.com/msantos7gabriel/editor-de-texto/commits"><img src="https://img.shields.io/github/last-commit/msantos7gabriel/editor-de-texto?style=flat-square&logo=git" alt="Último commit"></a>
    <a href="https://github.com/msantos7gabriel/editor-de-texto/issues"><img src="https://img.shields.io/github/issues/msantos7gabriel/editor-de-texto?style=flat-square&logo=github" alt="Issues abertas"></a>
</p>

## 👥 Integrantes

<table width="100%">
    <tr>
        <td align="center" width="33%">
            <a href="https://github.com/msantos7gabriel">
                <img src="https://avatars.githubusercontent.com/u/113394709?v=4" width="110px" alt="Gabriel Montalvão Santos"><br>
                <strong>Gabriel Montalvão Santos</strong>
            </a><br><br>
            <a href="https://github.com/msantos7gabriel"><img src="https://img.shields.io/github/followers/msantos7gabriel?label=seguidores&style=flat-square&logo=github" alt="Seguidores de Gabriel"></a><br>
            <a href="https://github.com/msantos7gabriel?tab=repositories"><img src="https://img.shields.io/badge/ver%20reposit%C3%B3rios-GitHub-181717?style=flat-square&logo=github" alt="Repositórios de Gabriel"></a>
        </td>
        <td align="center" width="33%">
            <a href="https://github.com/geovane-nves">
                <img src="https://avatars.githubusercontent.com/u/245179684?v=4" width="110px" alt="Geovane"><br>
                <strong>Geovane</strong>
            </a><br><br>
            <a href="https://github.com/geovane-nves"><img src="https://img.shields.io/github/followers/geovane-nves?label=seguidores&style=flat-square&logo=github" alt="Seguidores de Geovane"></a><br>
            <a href="https://github.com/geovane-nves?tab=repositories"><img src="https://img.shields.io/badge/ver%20reposit%C3%B3rios-GitHub-181717?style=flat-square&logo=github" alt="Repositórios de Geovane"></a>
        </td>
        <td align="center" width="33%">
            <a href="https://github.com/baianoo-cmd">
                <img src="https://avatars.githubusercontent.com/u/143428317?v=4" width="110px" alt="Enzo Dias"><br>
                <strong>Enzo Dias</strong>
            </a><br><br>
            <a href="https://github.com/baianoo-cmd"><img src="https://img.shields.io/github/followers/baianoo-cmd?label=seguidores&style=flat-square&logo=github" alt="Seguidores de Enzo"></a><br>
            <a href="https://github.com/baianoo-cmd?tab=repositories"><img src="https://img.shields.io/badge/ver%20reposit%C3%B3rios-GitHub-181717?style=flat-square&logo=github" alt="Repositórios de Enzo"></a>
        </td>
    </tr>
</table>

<div align="center">
    <a href="https://github.com/msantos7gabriel">@msantos7gabriel</a>
    &nbsp;&bull;&nbsp;
    <a href="https://github.com/geovane-nves">@geovane-nves</a>
    &nbsp;&bull;&nbsp;
    <a href="https://github.com/baianoo-cmd">@baianoo-cmd</a>
</div>

## ✨ Sobre o projeto

O programa oferece um ambiente interativo em terminal para editar arquivos de texto, com recursos de:

- inserção de linhas;
- remoção de linhas;
- desfazer e refazer operações;
- cópia e colagem de linhas via fila de transferência;
- salvamento de alterações em arquivo;
- navegação por teclado usando `ncurses`.

A lógica principal combina leitura/escrita de arquivos, controle de cursor e uso de estruturas de dados para manter o histórico e a área de transferência funcional.

### 🌟 Destaques

🧾 Edição de arquivos em texto via terminal.
🔁 Histórico de ações usando pilha (`Undo`/`Redo`).
📋 Área de transferência com fila FIFO para copiar e colar linhas.
🧠 Interface em terminal com `ncurses`.
💾 Salvar alterações diretamente no arquivo.
⚠️ Tratamento de arquivos vazios, erros de abertura e limites de entrada.

## 🛠️ Requisitos

- GCC ou outro compilador compatível com C11.
- GNU Make.
- Biblioteca `ncurses` instalada no sistema. Essa dependência é necessária porque a interface do editor usa a biblioteca `ncurses` para renderização em terminal.
- Sistema operacional Linux, macOS ou Windows com ambiente equivalente ao Make e ao `ncurses`.

### 📦 Instalação da dependência do Ncurses

No Linux (Debian/Ubuntu), execute:

```bash
sudo apt update
sudo apt install libncurses-dev
```

No macOS, com Homebrew:

```bash
brew install ncurses
```

## 🔨 Compilação

Na raiz do projeto, execute:

```bash
make
```

O `Makefile` compila todos os arquivos `.c` presentes no repositório com as opções `-Wall -Wextra -pedantic -std=c11` e gera o executável `egg`.

Para limpar os arquivos objeto e o executável:

```bash
make clean
```

## ▶️ Execução

Depois da compilação, execute:

```bash
./egg <caminho_do_arquivo>
```

Exemplo:

```bash
./egg texto.txt
```

O programa abre o arquivo em modo de edição e oferece as opções de interface por teclado:

```text
[I] Inserir linha
[A] Apagar linha
[U] Undo
[R] Redo
[C] Copiar linha
[V] Colar linha
[S] Salvar
[Q] Sair
```

Também há navegação com setas para cima e para baixo para mover o cursor na visualização do arquivo.

## 🗂️ Organização dos arquivos

```text
.
├── include/
│   ├── arquivos.h
│   ├── fila.h
│   ├── funcionalidades.h
│   └── pilha.h
├── src/
│   ├── arquivos.c
│   ├── fila.c
│   ├── funcionalidades.c
│   ├── main.c
│   └── pilha.c
├── Makefile
├── README.md
└── egg
```

## 📋 Funcionalidades implementadas

O sistema foi estruturado para realizar operações básicas de edição de texto em terminal:

1. Leitura e carregamento de um arquivo para edição.
2. Contagem de linhas do arquivo.
3. Inserção de nova linha no final do arquivo.
4. Remoção de linha específica.
5. Salvamento das alterações na memória do arquivo.
6. Histórico de ações com pilha LIFO para `Undo` e `Redo`.
7. Fila FIFO para cópia e colagem de linhas.
8. Renderização em tela com `ncurses` e barra lateral para área de transferência.
9. Controle de cursor e atualização da visualização conforme o texto.

## 🧠 Estruturas de dados utilizadas

- Pilha: usada para guardar as ações do histórico de desfazer/refazer.
- Fila: usada para armazenar as linhas copiadas para a área de transferência.
- Arquivo: manipulação direta em disco para persistência das alterações.

## 📌 Estado atual e pendências

- O editor de texto em terminal está funcional para edição básica de arquivos.
- A lógica de `Undo`/`Redo` está implementada e integrada ao fluxo principal.
- A funcionalidade de copiar e colar linhas via fila está ativa.
- O projeto utiliza `ncurses` para interface visual em terminal.
- Há potencial para evoluir com busca textual, edição de caracteres em linha, navegação mais avançada e melhorias de usabilidade.

## 🧭 Objetivo didático

O projeto tem caráter acadêmico e demonstra, na prática, o uso de:

- listas e filas em memória;
- comportamentos LIFO e FIFO;
- interação com arquivos em linguagem C;
- criação de interfaces em terminal com `ncurses`;
- organização modular em arquivos de cabeçalho e implementação.

## 🔗 Repositório

- GitHub: [msantos7gabriel/editor-de-texto](https://github.com/msantos7gabriel/editor-de-texto)
