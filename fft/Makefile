CC = gcc

all: dft

dft: dft.o utility.o
	$(CC) -lm $^ -o $@

%.o: %.c utility.h
	$(CC) -Wall -c $<

clean:
	rm -f dft *.o
