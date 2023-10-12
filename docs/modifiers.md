# Modifiers
Modifiers can change how a variable or method is presented to the compiler and user. They can apply to struct fields or methods.

## `static`
A static variable or method does not require an instance of a type. Instead you can call a function of a type as if it were a variable.

```
struct MyStruct 
{
    static i32 myNumber = 4;
}
```
```
print(MyStruct.myNumber); // "4"
```