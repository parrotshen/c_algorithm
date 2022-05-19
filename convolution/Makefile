CC = gcc

all: convolution

convolution: convolution.o
	$(CC) -o $@ $<

%.o: %.c
	$(CC) -Wall -c $<

clean:
	rm -f convolution *.o
