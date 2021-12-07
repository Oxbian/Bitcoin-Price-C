CC ?= gcc
LIBS = -lcurl -ljson-c
SRCDIR = src

SRC = bitcoinCounter.c bitcoinapi.c

OBJS = $(SRC:.c=.o)

all: bitcoinprice

%.o: $(SRCDIR)/%.c
	$(CC) -c -o $(@F) $(LIBS) $<

bitcoinprice: $(OBJS)
	$(shell cd ..)
	$(CC) -o $(@F) $(OBJS) $(LIBS)
	$(MAKE) clean

clean: 
	rm *.o