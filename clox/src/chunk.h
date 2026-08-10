#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

typedef struct {
  uint16_t *lines;
  uint16_t *counts;
  int len;
  int cap;
} LineInfo;

void initLineInfo(LineInfo *li);
void writeLineInfo(LineInfo *li, uint16_t line);
void freeLineInfo(LineInfo *li);
int getLine(LineInfo *li, int index);

typedef struct {
  ValueArray constants;
  LineInfo lines;
  uint8_t *code;
  int len;
  int cap;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, uint16_t line);
int addConstant(Chunk *chunk, Value value);

#endif
