CC = gcc

all: diffie-hellman

diffie-hellman: diffie-hellman.c
	$(CC) $< -Wall -lgmp -o $@

clean:
	rm -f diffie-hellman

.PHONY: diffie-hellman clean
