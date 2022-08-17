CC = gcc

all: power_quantity field_quantity power_gain field_gain

power_quantity: power_quantity.c
	$(CC) -o $@ -Wall -lm $<

field_quantity: field_quantity.c
	$(CC) -o $@ -Wall -lm $<

power_gain: power_gain.c
	$(CC) -o $@ -Wall -lm $<

field_gain: field_gain.c
	$(CC) -o $@ -Wall -lm $<

clean:
	rm -f power_quantity field_quantity power_gain field_gain
