CC = gcc
CFLAGS = -Wall -DUSING_MACRO=1
LDFLAGS = 

APPS += addition
APPS += subtraction
APPS += multiplication
APPS += scalar
APPS += transposition
APPS += identity

all: $(APPS)

addition: addition.o util.o
	$(CC) $(LDFLAGS) $^ -o $@

subtraction: subtraction.o util.o
	$(CC) $(LDFLAGS) $^ -o $@

multiplication: multiplication.o util.o
	$(CC) $(LDFLAGS) $^ -o $@

scalar: scalar.o util.o
	$(CC) $(LDFLAGS) $^ -o $@

transposition: transposition.o util.o
	$(CC) $(LDFLAGS) $^ -o $@

identity: identity.o util.o
	$(CC) $(LDFLAGS) $^ -o $@


%.o: %.c util.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(APPS) *.o
