.PHONY: all
.PHONY: clean
.PHONY: main.c

all: main.c src/lexer.c

main.c:
	gcc -Wall -o main.o main.c  src/file_reader.c src/lexer.c src/parser.c src/tokens.c

run: main.c  src/file_reader.c src/lexer.c src/parser.c src/tokens.c
	./main.o

clean:
	-rm *.o