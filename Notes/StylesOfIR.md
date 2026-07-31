# Styles Of Intermediate Representations

## Control Flow Graph
It is the representation of all paths that might be traversed through a function
during its execution or control flow. It is a directed graph with basic block of
execution as vertex and control flow between them as edges.

Typically a function has two specifically designated blocks: entry block (through
which the control enters the function) and exit block (through which the control
exits the function). A function may have multiple exit blocks or none.

### Example

```c
void print_within_parens(const char *s) {
  printf("(")             // 1
  if (s != NULL) {        // 1
    printf("%s", s);      // 2
  }                       // 2
  printf(")");            // 3
}
```

### Resources
- https://en.wikipedia.org/wiki/Control-flow_graph

## Static Single Assignment
It is a type of intermediate representation where each variable is assigned exactly
once. Used in LLVM, GCC etc.

It makes various optimizations easier to perform.

### References
- https://en.wikipedia.org/wiki/Static_single-assignment_form

## Continuation Passing Style

### Resources
- https://en.wikipedia.org/wiki/Continuation-passing_style

## Three Address Code 

### Resources
- https://en.wikipedia.org/wiki/Three-address_code
