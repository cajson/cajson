CC = gcc
CFLAGS = -g -I ./src -std=gnu11 
OBJS = cj

all: $(OBJS)

cj: src/cj.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./cj prog/hello.cj
	./cj prog/stmt1.cj
	./cj prog/fn.cj
	./cj prog/matrix.cj
	./cj prog/array.cj
	./cj prog/sum.cj
	./cj prog/for.cj
	./cj prog/comment.cj
	./cj prog/exp1.cj
	./cj prog/mt.cj

#	./cj prog/if.cj

test: $(OBJS)
	./cj prog/exp1.cj

clean:
	rm -f $(OBJS)
