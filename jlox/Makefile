.PHONY: build run clean

build:
	mkdir -p bin
	javac -d bin -sourcepath src src/*.java

run: build
	rlwrap java -cp bin Lox $(FILE)

clean:
	rm -rf bin
