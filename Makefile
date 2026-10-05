# 1. Configurações Iniciais
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g -lncursesw
TARGET = egg

# 2. A MÁGICA ESTÁ AQUI: Procura arquivos .c em todas as pastas e subpastas
SRCS = $(shell find . -type f -name '*.c')

# Troca a extensão de .c para .o (os .o ficarão nas mesmas pastas dos .c)
OBJS = $(SRCS:.c=.o)

# 3. Regra principal
all: $(TARGET)

# 4. Junta tudo no programa final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 5. Compila cada .c no seu respectivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 6. Faxina geral (apaga os .o de TODAS as pastas)
clean:
	rm -f $(OBJS) $(TARGET)