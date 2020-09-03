compiler_run = gcc -Wall -o main.cua.o main.c
C_SRC = $(wildcard src/*.c)
H_SRC = $(wildcard src/*.h)
CHECK_MEMORY = valgrind ./main.cua.o

.PHONY: Cua
.PHONY: clean
.PHONY: memory_check

CuaFile=n

Cua: ${C_SRC} ${H_SRC}
	${compiler_run} ${C_SRC} ${H_SRC}

memory_check: ${C_SRC}
	${CHECK_MEMORY} ${CuaFile}

clean: ${C_SRC} ${H_SRC}
	rm *.o