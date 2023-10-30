# Arrays

Arrays are a collection of sequential data. They can either have a fixed size which is defined at compile-time, or
a dynamic size which is defined at run-time.

## Syntax

### Creating a fixed size array

```
<Type>[<Size>] <Name>;
```

> **Note:** The size of the array must be a constant expression or literal.
> Fixed size arrays live on the stack, therefore their size can not be larger than the size of a stack frame on the target platform (e.g. on Linux 8MiB). Attempting to do so will throw a compile-time error.

### Creating a dynamically sized array

#### On the heap

```
<Type>[] <Name> = heap <Size>;
```

#### On the stack

```
<Type>[] <Name> = stack <Size>;
```

> **Note:** If a dynamically sized array on the heap is being referenced by any other variable, it will live until the reference gets destroyed. Otherwise, it will live until the stack frame where it was created, gets popped.

### Accessing array elements

Arrays use 0-based indexing. This means that an array with `n` elements has its first element at 0 and its last element at `n-1`.

#### Getting a value

```
<Variable> = <Name>[<Index>];
```

#### Setting a value

```
<Name>[<Index>] = <Variable>;
```

### Getting the size of an array

```
usize <Variable> = sizeof <Array>;
```

## Overloading the array access operator

The [array access operator](operators.md#other) can be overloaded with any amount of arguments, but at least one argument. Here's a quick **example**:

```
struct Matrix44
{
    float[4 * 4] data;

    operator[](i32 row, i32 col)
    {
        return data[row + 4 * col];
    }
}

main
{
    Matrix44 mat = new Matrix44;
    mat[0, 0] = 1.0f;
    mat[1, 1] = 1.0f;
    mat[2, 2] = 1.0f;
    mat[3, 3] = 1.0f;
}
```
