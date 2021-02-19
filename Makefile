CFLAGS=-std=c11 -g -static

comp: comp.c

test: 9cc
	./tester.sh

clean:
	rm -f comp *.o *~ tmp2*

.PHONY: test clean
