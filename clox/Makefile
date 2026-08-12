CFLAGS := -Wall -Werror -Wpedantic -O2
CC := cc $(CFLAGS)

.PHONY: clean

run: clox
	rlwrap ./build/clox

clox: main.o chunk.o memory.o debug.o value.o vm.o compiler.o scanner.o | build
	$(CC) -o build/$@ $(addprefix build/,$^)

main.o: src/main.c | build
	$(CC) -c -o build/$@ $^
	
chunk.o: src/chunk.c | build
	$(CC) -c -o build/$@ $^

debug.o: src/debug.c | build
	$(CC) -c -o build/$@ $^

memory.o: src/memory.c | build
	$(CC) -c -o build/$@ $^

value.o: src/value.c | build
	$(CC) -c -o build/$@ $^

vm.o: src/vm.c | build
	$(CC) -c -o build/$@ $^

compiler.o: src/compiler.c | build
	$(CC) -c -o build/$@ $^

scanner.o: src/scanner.c | build
	$(CC) -c -o build/$@ $^

build:
	mkdir -p build

clean:
	rm -f build/*
