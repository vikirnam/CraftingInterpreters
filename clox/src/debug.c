#include "debug.h"
#include "chunk.h"
#include "value.h"
#include <stdio.h>

void disassembleChunk(Chunk *chunk, const char *name)
{
	printf("== %s ==\n", name);

	for (int offset = 0; offset < chunk->len;) {
		offset = disassembleInstruction(chunk, offset);
	}
}

static int simpleInstruction(const char *name, int offset)
{
	printf("%s\n", name);
	return offset + 1;
}

void printValue(Value value)
{
	printf("%g", value);
}

static int constantInstruction(const char *name, Chunk *chunk, int offset)
{
	uint8_t constant = chunk->code[offset + 1];
	printf("%-16s %4d '", name, constant);
	printValue(chunk->constants.values[constant]);
	printf("'\n");
	return offset + 2;
}

int disassembleInstruction(Chunk *chunk, int offset)
{
	printf("%04d ", offset);

	if (offset > 0 && getLine(&chunk->lines, offset) ==
				  getLine(&chunk->lines, offset - 1)) {
		printf("   | ");
	} else {
		printf("%4d ", getLine(&chunk->lines, offset));
	}
	uint8_t ins = chunk->code[offset];
	switch (ins) {
	case OP_RETURN:
		return simpleInstruction("OP_RETURN", offset);
	case OP_CONSTANT:
		return constantInstruction("OP_CONSTANT", chunk, offset);
	default:
		printf("Unknown opcode %d\n", ins);
		return offset + 1;
	}
}
