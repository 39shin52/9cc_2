CFLAGS=-std=c11 -g -static

comp: comp.c

test: comp
	./tester.sh

clean:
	rm -f comp *.o *~ tmp2*

.PHONY: test clean
