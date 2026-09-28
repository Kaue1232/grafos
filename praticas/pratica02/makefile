CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = programa

SRCS = main.c busca_largura.c busca_profundidade.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)