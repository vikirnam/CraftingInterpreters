#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk *chunk) {
  chunk->len = 0;
  chunk->cap = 0;
  chunk->code = NULL;
  initValueArray(&chunk->constants);
  initLineInfo(&chunk->lines);
}

void writeChunk(Chunk *chunk, uint8_t byte, uint16_t line) {
  if (chunk->cap < chunk->len + 1) {
    int old_cap = chunk->cap;
    chunk->cap = GROW_CAPACITY(old_cap);
    chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_cap, chunk->cap);
  }

  writeLineInfo(&chunk->lines, line);

  chunk->code[chunk->len] = byte;
  chunk->len++;
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->len);
  freeValueArray(&chunk->constants);
  freeLineInfo(&chunk->lines);
  initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.len - 1;
}

// -------------------- LineInfo ------------------------
void initLineInfo(LineInfo *li) {
  li->len = 0;
  li->cap = 0;
  li->lines = 0;
  li->counts = NULL;
}

void writeLineInfo(LineInfo *li, uint16_t line) {
  if (li->len > 0 && li->lines[li->len - 1] == line) {
    li->counts[li->len - 1]++;
    return;
  }

  if (li->cap < li->len + 1) {
    int old_cap = li->cap;
    li->cap = GROW_CAPACITY(old_cap);
    li->lines = GROW_ARRAY(uint16_t, li->lines, old_cap, li->cap);
    li->counts = GROW_ARRAY(uint16_t, li->counts, old_cap, li->cap);
  }
  li->lines[li->len] = line;
  li->counts[li->len] = 1;
  li->len++;
}

void freeLineInfo(LineInfo *li) {
  FREE_ARRAY(uint16_t, li->lines, li->len);
  FREE_ARRAY(uint16_t, li->counts, li->len);
  initLineInfo(li);
}

int getLine(LineInfo *li, int index) {
  int result = 0;
  for (int i = 0; i < li->len; i++) {
    index -= li->counts[i];
    if (index < 0) {
      result = li->lines[i];
      break;
    } 
  }
  return result;
}

