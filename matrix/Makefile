CC = gcc
CFLAGS = -Wall -DUSING_MACRO=1
LDFLAGS = 

APPS += addition
APPS += subtraction
APPS += multiplication
APPS += scalar
APPS += transposition
APPS += determinant
APPS += identity

all: $(APPS)

addition: addition.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@

subtraction: subtraction.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@

multiplication: multiplication.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@

scalar: scalar.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@

transposition: transposition.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@

determinant: determinant.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@

identity: identity.o matrix.o
	$(CC) $(LDFLAGS) $^ -o $@


%.o: %.c matrix.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(APPS) *.o
