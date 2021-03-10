CC = gcc

all: qm_mini

qm_mini: main.o qm.o
	$(CC) -lm $^ -o $@

%.o: %.c qm.h
	$(CC) -Wall -c $<

clean:
	rm -f *.o qm_mini
