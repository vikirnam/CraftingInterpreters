#ifndef CLOX_TABLE_H
#define CLOX_TABLE_H

// TODO: Implement Robin Hood Hashing (preferably after the implemenatation if complete to bench)
// Resource:
//   - https://cs.uwaterloo.ca/research/tr/1986/CS-86-14.pdf
//   - https://www.sebastiansylvan.com/post/robin-hood-hashing-should-be-your-default-hash-table-implementation/

#include "common.h"
#include "value.h"

typedef struct {
  ObjString *key;
  Value value;
} Entry;

typedef struct {
  int count;
  int cap;
  Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableGet(Table *table, ObjString *key, Value *value);
bool tableSet(Table *table, ObjString *key, Value value);
bool tableDelete(Table *table, ObjString *key);
void tableAddAll(Table *from, Table *to);
ObjString *tableFindString(Table *table, const char *chars, int len, uint32_t hash);

#endif
