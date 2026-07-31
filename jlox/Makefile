.PHONY: build run clean

gen-ast:
	javac -d bin -sourcepath tool tool/GenerateAst.java
	java -cp bin GenerateAst src

build:
	mkdir -p bin
	javac -d bin -sourcepath src src/*.java

run: build
	rlwrap java -cp bin Lox $(FILE)

clean:
	rm -rf bin
