CC = gcc
CFLAGS = -Wall -g -I ./src -std=gnu11 
OBJS = cj

all: $(OBJS)

cj: src/cj.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./cj prog/hello.cj
	./cj prog/fn.cj
	./cj prog/matrix.cj
	./cj prog/for.cj
	./cj prog/comment.cj
	./cj prog/exp1.cj
	./cj prog/mt.cj
	./cj prog/pid1.cj
	./cj prog/if.cj
	./cj prog/stmt1.cj
	./cj prog/sum.cj
	./cj prog/sum2.cj
	./cj prog/array.cj
	./cj prog/array2.cj

test: $(OBJS)
	./cj prog/exp1.cj

clean:
	rm -f $(OBJS)
