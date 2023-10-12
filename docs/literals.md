# Literals

Literals are concrete and absolute values that can't be modified at run time.

There are 6 types of literals:
- Integer literals
- Floating point literals
- Boolean literals
- Character literals
- String literals
- Array literals

## Integer literals
> **Note:** By default, attempting to store a value with an integer type that's not large enough to fit the literal will wrap around the number (e.g. ) and results in a warning.
- Decimal numbers: 
    - `5`
    - `-999`
    - `1_000_000_000`

> **Note:** By default, assigning a negative decimal literal to an unsigned integer (`u8`, `u16`, `u32`, `u64` or `usize`) will store the 2's complement of that value (e.g. if `u16 foo = -1;`, then `foo` will evaluate to `0xFFFFFFFF`) and results in a warning. In *safe mode*, attempting this will result in a compile-time error.

- Hexadecimal numbers:
    - `0xA`
    - `0xC0FFEE`
    
- Binary numbers:
    - `0b101`
    - `0b10000001`
    - `0b1111_1001`