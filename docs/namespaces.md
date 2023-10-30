# Namespaces

A namespace is a collection of types and functions that belong to one part of a program or library. It solves problems like conflicting type names from multiple sources.

Importing a library will add all functions of the specified library to your code.

## Syntax

### Including a namespace

The `include` keyword can be used to add external namespaces to your project.

```
include <Name>;
```

### Aliasing namespaces

```
include <Name> as <Alias>;
```

### Including a dynamically linked library

The `include` keyword can also be used to load dynamically linked libraries with the Foreign Function Interface (FFI).
If you import a dynamically linked library, you need to manually specify the imported functions and their signatures for them to be recognized.
You also need to give them an alias as their file name might not qualify as a valid namespace.

> **Note:** Memory and type safety can't be guaranteed when using FFI functions. Therefore, you have to enable unsafe code in your project in order to be able to call any function included through the FFI.

```
include "<File name>" as <Name>
{
    <Function signatures>
}
```

## Example

```
include std;
include MyExternalLibrary;

include "test.dll" as Test
{
    WriteText(str text);
}

main
{
    MyExternalLibrary.MyFunction();
    Test.WriteText("Hello, World!");
}
```
