CC = gcc

all: findpeaks

findpeaks: findpeaks.o
	$(CC) -o $@ $<

%.o: %.c
	$(CC) -Wall -c $<

clean:
	rm -f findpeaks *.o
