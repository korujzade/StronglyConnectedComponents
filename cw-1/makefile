CC=gcc
CFLAGS=-Wall -g -std=c99
LDFLAGS=-lm
HEADERS=graph.h stack.h

%.o: $(HEADERS)
 
tarjan: tarjan.o graph_functions.o stack.o

clean:
	rm -f tarjan.o graph_functions.o
