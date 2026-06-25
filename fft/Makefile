CC = gcc

all: fft fft_shift dft_detail

fft: fft.o utility.o
	$(CC) $^ -lm -o $@

fft_shift: fft_shift.o utility.o
	$(CC) $^ -lm -o $@

dft_detail: dft_detail.o utility.o
	$(CC) $^ -lm -o $@

%.o: %.c utility.h
	$(CC) -Wall -c $<

clean:
	rm -f fft fft_shift dft_detail *.o
