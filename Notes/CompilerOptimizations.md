# Compiler Optimizations

## Constant Propagation
Substitute the variables whose values are known to be constant.

### Resources
- https://en.wikipedia.org/wiki/Constant_folding#Constant_propagation
- https://en.wikipedia.org/wiki/Sparse_conditional_constant_propagation

## Common Subexpression Elimination
Search for matching expressions that evaluate to same value and replace them with
a variable holding the computed value.

### Resources
- https://en.wikipedia.org/wiki/Common_subexpression_elimination

## Loop Invariant Code Motion
Loop Invariant Code is a piece of code consisting of statements and expressions
that can be moved outside of a loop without affecting the program semantics. Loop
Invariant Code Motion is the automatic process of doing just that.

### Resources
- https://en.wikipedia.org/wiki/Loop-invariant_code_motion

## Global Value Numbering
Assign a value number to variables and expression. Same number is assigned to those
variable and expressions that are equivalent.

### Resources
- https://en.wikipedia.org/wiki/Value_numbering#Global_value_numbering

## Strength Reduction
Expensive operations are replaced by equivalent but less expensive operations.

### Resources
- https://en.wikipedia.org/wiki/Strength_reduction

## Scalar Replacement of Aggregates
Breaks aggregates like structs or arrays into member level.

### Resources
- https://debasishg.github.io/blog/sroa/

## Dead Code Elimination
Remove codes that doesn't affect the programs result. 

### References
- https://en.wikipedia.org/wiki/Dead-code_elimination

## Loop Unrolling

### Resources
- https://en.wikipedia.org/wiki/Loop_unrolling

## General Resources

- https://blog.regehr.org/archives/1603
