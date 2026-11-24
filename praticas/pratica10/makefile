CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O3 -march=native -DNDEBUG
LDFLAGS :=

TARGET  := pratica10
SRCS    := main.c hamiltoniano.c tps.c
OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c hamiltoniano.h tps.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)