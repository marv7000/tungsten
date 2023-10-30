# Functions

Everything a program does is defined in a function.

## Syntax

### Creating a function

Create a new function declaration by stating its return type or `void` for no return value, followed by a name and braces.
Inside of the braces you can have zero or an arbitrary amount of parameters you want to pass onto the function.

```
<Type> <Name>(<Parameter1>, <Parameter2>, ...)
```

We also need to define what this function is supposed to do. Below the function declaration, add the "body" by adding curly braces and a `return` statement (unless the return type is `void`), as well as a semicolon after the return value.

```
{
    ...
    return <Variable with type <Type>>;
}
```

### Calling a function

To call a function, type out the name of the function you want to call followed by braces and potential parameters and a semicolon at the end.

```
<Name>(<Parameter1>, <Parameter2>, ...);
```

## Overloading

You can create multiple functions of the same name with different return types and parameters.

> **Note:** If two functions have none or the same parameter type(s), it **can't** be overloaded, even if the return type varies.

### Examples

```
include std;

void write(String foo)
{
    print(foo);
}

void write(i32 bar)
{
    print((String)bar);
}
```

### Incorrect Usage

```
void read() { }
i32 read() { } // Compile-time error
```
