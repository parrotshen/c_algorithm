CC = gcc

all: float double minimum-float minimum-double

float: float.c
	$(CC) -Wall $< -o $@

double: double.c
	$(CC) -Wall $< -o $@

minimum-float: minimum-float.c
	$(CC) -Wall $< -o $@

minimum-double: minimum-double.c
	$(CC) -Wall $< -o $@

clean:
	rm -f float double minimum-float minimum-double
