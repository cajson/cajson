CC = gcc
CFLAGS = -Wall -g -I ./src -std=gnu11 
OBJS = cj

all: $(OBJS)

cj: src/cj.c src/gen_js.c src/gen_cj.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./cj prog/sum.cj -o out/sum.js
	deno run out/sum.js

test: $(OBJS)
	./cj2x_test.sh cj
	./cj2x_test.sh js

clean:
	rm -f $(OBJS)
