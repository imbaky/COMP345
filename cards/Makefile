CC=g++

WARN=-Wall -W -Wno-missing-field-initializers
OPT=-O2

CFLAGS=$(WARN) $(OPT)

all:
	$(CC) $(CFLAGS) card.cpp card.h main.cpp -o main

.PHONY: all

clean:
	rm -rf card.h.gch main

.PHONY: clean

