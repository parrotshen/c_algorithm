CC = gcc
APP_1 = test_aes128
APP_2 = test_aes128_cbc
APP_3 = test_aes128_ctr


##################
# Source
##################

SRC += test_aes128.c
SRC += test_aes128_cbc.c
SRC += test_aes128_ctr.c
SRC += crypto_aes.c
SRC += ../utility/utility.c


##################
# CFLAGS
##################

CFLAGS += -Wall
CFLAGS += -D_LITTLE_ENDIAN_
CFLAGS += -I../utility/


##################
# LDFLAGS
##################

LDFLAGS += 


#################
# Build
#################

OBJS = $(SRC:.c=.o)

all: $(APP_1) $(APP_2) $(APP_3)

$(APP_1): test_aes128.o crypto_aes.o ../utility/utility.o
	$(CC) $(LDFLAGS) $^ -o $@

$(APP_2): test_aes128_cbc.o crypto_aes.o ../utility/utility.o
	$(CC) $(LDFLAGS) $^ -o $@

$(APP_3): test_aes128_ctr.o crypto_aes.o ../utility/utility.o
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(APP_1) $(APP_2) $(APP_3) $(OBJS)

.PHONY: all clean
