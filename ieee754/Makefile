CC = gcc

all: float double extreme-float extreme-double

float: float.c
	$(CC) -Wall $< -o $@

double: double.c
	$(CC) -Wall $< -o $@

extreme-float: extreme-float.c
	$(CC) -Wall $< -o $@

extreme-double: extreme-double.c
	$(CC) -Wall $< -o $@

clean:
	rm -f float double extreme-float extreme-double
