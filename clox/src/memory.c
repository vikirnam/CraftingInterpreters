#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"
#include <stdlib.h>

void *reallocate(void *ptr, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(ptr);
    return NULL;
  }

  void *result = realloc(ptr, new_size);
  if (result == NULL) exit(1);
  return result;
}

static void freeObject(Obj *object) {
  switch (object->type) {
    case OBJ_STRING: {
        ObjString *string = (ObjString *)object;
        FREE_ARRAY(char, string->chars, string->len + 1);
        FREE(ObjString, object);
        break;
      }
  }
}

void freeObjects(void) {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    freeObject(object);
    object = next;
  }
}

