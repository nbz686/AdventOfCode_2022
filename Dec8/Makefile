CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -g
LDFLAGS=-lm
PROGRAMS=Dec8
TESTS=..

.PHONY: all test clean ../src.zip

all: $(PROGRAMS)

Dec1_NumKcal: Dec1_NumKcal.o 
	gcc -o $@ $^ $(LDFLAGS)

clean: 
	rm -rf $(PROGRAMS)  *.o core