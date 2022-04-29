CC = gcc
CFLAGS = -g -I ./src
OBJS = obj_test lex_test parse_test

all: $(OBJS)

obj_test: test/obj_test.c
	$(CC) $(CFLAGS) $^ -o $@

lex_test: test/lex_test.c
	$(CC) $(CFLAGS) $^ -o $@

parse_test: test/parse_test.c
	$(CC) $(CFLAGS) $^ -o $@

cj: src/cj.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./obj_test
	./parse_test prog/stmt1.cj

#	./lex_test prog/hello.cj

clean:
	rm -f $(OBJS)
