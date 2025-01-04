CC = gcc

all: dft dft_detail

dft: dft.o utility.o
	$(CC) $^ -lm -o $@

dft_detail: dft_detail.o utility.o
	$(CC) $^ -lm -o $@

%.o: %.c utility.h
	$(CC) -Wall -c $<

clean:
	rm -f dft dft_detail *.o
