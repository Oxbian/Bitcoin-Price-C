CC ?= gcc
LIBS = -lcurl -ljson-c

SRC = bitcoinCounter.c bitcoinapi.c

OBJS = $(SRC:.c=.o)

all: bitcoinprice

%.o: %.c
	$(CC) -c -o $(@F) $(LIBS) $<

bitcoinprice: $(OBJS)
	$(shell cd ..)
	$(CC) -o $(@F) $(OBJS) $(LIBS)
	$(MAKE) clean

clean: 
	rm *.o