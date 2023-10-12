# References

By default, every type in Tungsten is a value type. A reference can point to any value type and modifying a reference will modify the value behind it. A reference can be constant or mutable.
Create a reference type by adding the `ref` keyword before the type.

## Syntax
### Constant/Immutable references
```
const ref TypeName varName = ...;
```
### Mutable references
```
ref TypeName varName = ...;
```
> **Note**: References always have to be assigned to a variable, assigning to a literal is not allowed.


## Example
This code adds 1 to the referenced `integer`. This will not only affect `integer` inside the function, but also `num` outside of it.

```
void addOne(ref i32 integer) {
    integer += 1;
}
```

```
i32 num = 0;
addOne(num);
print(num); // "1"
```

It's possible to create new references inside of a function call. These are only available in the return scope and get deleted after.
```
addOne(ref i32 num) {
    print(num); // "1"
}
```

### Incorrect Usage

```
addOne(0); // Assigning a literal to a mutable reference.
```

```
addOne(ref i32 num = 0);
print(num); // Deleted variable "num".
```