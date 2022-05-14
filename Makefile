CC = gcc
CFLAGS = -Wall -g -I ./src -std=gnu11 
OBJS = cj

all: $(OBJS)

cj: src/cj.c src/gen_js.c src/gen_cj.c src/gen_c.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./cj prog/sum.cj -o out/sum.js
	deno run out/sum.js

test: $(OBJS)
	./cj2js.sh

clean:
	rm -f $(OBJS)
