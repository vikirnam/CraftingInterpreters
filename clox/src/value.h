#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

typedef double Value;

typedef struct {
  Value *values;
  int len;
  int cap;
} ValueArray;

void initValueArray(ValueArray *va);
void writeValueArray(ValueArray *va, Value value);
void freeValueArray(ValueArray *va);

#endif
