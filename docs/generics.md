# Generics
Generics take a type as an argument, which can be used as a substitute type in struct fields and/or methods and be replaced at compile time.
The generic type can be either a primitive type or a struct, but it **can't** be:
- Reference types
- Error types

### Examples
---
In this example, we create a linked list node with a variable value type.

```
struct LinkedList<MyType>
{
    LinkedList^ next;
    MyType value;
}
```