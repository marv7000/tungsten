# Dynamic Memory
Every fixed length array lives on the stack by default and can't be deleted.

The keywords `stack` and `heap` will let you dynamically allocate references and non-fixed sized arrays.
`delete` will free the memory used by any object allocated by the `heap` keyword.

If you want the compiler to pick and optimize use `new` instead of `stack` or `heap`;

## Example
This code creates a new struct `Person` and allocates it on the heap, then deletes it.

```si
struct Person
{
    str name;
    i32 age;

    operator (str)
    {

    }
}
```
```si
Person^ coworker = heap Person();
print(coworker.name);
```