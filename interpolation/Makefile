CC = gcc

all: linear_interp polynomial_interp cspline_interp

linear_interp: linear_interp.c
	$(CC) $< -Wall -lm -o $@

polynomial_interp: polynomial_interp.c
	$(CC) $< -Wall -lm -o $@

cspline_interp: cspline_interp.c
	$(CC) $< -Wall -lm -o $@

clean:
	rm -f linear_interp polynomial_interp cspline_interp
