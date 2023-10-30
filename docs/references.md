# References

By default, every type in _Tungsten_ is a value type. A reference can point to any value type and modifying a reference will modify the value behind it.

> **Note:** _Tungsten_ uses `^` instead of `*` to avoid confusion between references and C-style pointers as references can't be used for mathematical expressions.

## Syntax

Create a reference type by adding the `^` symbol after the type name.

```
<Type>^ <Name> = ...;
```

> **Note:** References always have to be assigned to a variable, assigning to a literal is not allowed.

## Examples

This code adds 1 to the referenced `integer`. This will also affect the referenced variable `num` outside of the function.

```
void addOne(i32^ integer)
{
    integer += 1;
}
```

```
main
{
    i32 num = 0;
    addOne(num);
    print(num); // Prints "1".
}
```

It's possible to create new references inside of a function call. These are only available in the return scope and get discarded after.

```
main
{
    addOne(i32^ num)
    {
        print(num); // Prints "1".
    }
}
```

### Incorrect Usage

```
main
{
    addOne(0); // Compiler error.

    addOne(i32^ num = 0)
    {
        print(num);
    }
    print(num); // Compiler error.
}
```
