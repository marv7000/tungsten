# Overloading
You can create multiple functions of the same name with different return types and parameters.
> **Note:** If two functions have none or the same parameter type(s), it **can't** be overloaded, even if the return type varies.

## Examples
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
i32 read() { } // Compiler error
```