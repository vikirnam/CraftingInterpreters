CFLAGS := -Wall -Werror -Wpedantic -O2
CC := cc $(CFLAGS)

.PHONY: clean

clox: main.o chunk.o memory.o debug.o value.o vm.o
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


build:
	mkdir -p build

clean:
	rm -f build/*
