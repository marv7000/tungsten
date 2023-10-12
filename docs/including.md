# Including (`include`)

The `include` keyword can be used to add external libraries. 
It can also be used to load dynamically linked libraries (e.g. `.dll` on Windows, `.so` on Linux).

Importing a library will add all functions of the specified library to your code.
If you import a dynamically linked library, you need to manually specify the imported functions and their signatures for them to be recognized. They are always static.

### Usage
---

Import a built-in or source library:
```
include <Name of the library>;
```

Import a dynamically linkable library:
```
include "<Relative path to the library>"
{
    <function signature>;
}
```

### Example
---

```
include std;
include MyExternalLibrary;

include "test.dll"
{
    WriteText(str text, i32 textLength);
}
```