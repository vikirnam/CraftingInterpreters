#include "memory.h"
#include <stdio.h>
#include "value.h"
#include "object.h"
#include <string.h>

void initValueArray(ValueArray *va)
{
	va->len = 0;
	va->cap = 0;
	va->values = NULL;
}

void writeValueArray(ValueArray *va, Value value)
{
	if (va->cap < va->len + 1) {
		int old_cap = va->cap;
		va->cap = GROW_CAPACITY(old_cap);
		va->values = GROW_ARRAY(Value, va->values, old_cap, va->cap);
	}

	va->values[va->len] = value;
	va->len++;
}
void freeValueArray(ValueArray *va)
{
	FREE_ARRAY(Value, va->values, va->len);
	initValueArray(va);
}

void printValue(Value value)
{
	switch (value.type) {
	case VAL_BOOL:
		printf(AS_BOOL(value) ? "true" : "false");
		break;
	case VAL_NIL:
		printf("nil");
		break;
	case VAL_NUMBER:
		printf("%g", AS_NUMBER(value));
		break;
	case VAL_OBJ:
		printObject(value);
		break;
	}
}

bool valuesEqual(Value a, Value b)
{
	if (a.type != b.type)
		return false;
	switch (a.type) {
	case VAL_BOOL:
		return AS_BOOL(a) == AS_BOOL(b);
	case VAL_NIL:
		return true;
	case VAL_NUMBER:
		return AS_NUMBER(a) == AS_NUMBER(b);
	case VAL_OBJ: {
			ObjString* aString = AS_STRING(a);
			ObjString* bString = AS_STRING(b);
			return aString->len == bString->len && memcmp(aString->chars, bString->chars, aString->len) == 0;
		}
	default:
		return false;
	}
}
