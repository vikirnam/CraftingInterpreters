#include "memory.h"
#include "value.h"

void initValueArray(ValueArray *va) {
  va->len = 0;
  va->cap = 0;
  va->values = NULL;
}

void writeValueArray(ValueArray *va, Value value) {
  if (va->cap < va->len + 1) {
    int old_cap = va->cap;
    va->cap = GROW_CAPACITY(old_cap);
    va->values = GROW_ARRAY(Value, va->values, old_cap, va->cap);
  }

  va->values[va->len] = value;
  va->len++;
  
}
void freeValueArray(ValueArray *va) {
  FREE_ARRAY(Value, va->values, va->len);
  initValueArray(va);
}

