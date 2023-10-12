# Operators
Operators take a left hand and right hand input and combine both to produce a new value.
Almost all of them can be [overloaded](overloading.md) by the user.

## Arithmetic
| Symbol | Description |
| --- | --- |
| `+`  | Addition
| `-`  | Subtraction
| `*`  | Multiplication
| `/`  | Division
| `%`  | Modulo
| `**` | Exponent

## Binary
| Symbol | Description |
| --- | --- |
| `\|` | Bitwise Or
| `&`  | Bitwise And
| `^`  | Bitwise Exclusive Or
| `<<` | Bitwise Shift Left
| `>>` | Bitwise Shift Right

> All arithmetic and binary operators can be combined with the assignment operator:
> ```
> myInt *= 5;  // myNum = myNum * 5; 
> myInt <<= 3; // myNum = myNum << 3;
> ```

## Logical
| Symbol | Description |
| --- | --- |
| `\|\|` | Logical Or
| `&&`   | Logical And
| `!`    | Logical Not
| `==`   | Logical Equal
| `!=`   | Logical Not Equal

## Other
| Symbol | Description |
| --- | --- |
| `\|\|` | Logical Or
| `&&`   | Logical And
| `!`    | Logical Not
| `==`   | Logical Equal
| `!=`   | Logical Not Equal

# Exceptions
These operators are built into the language and can't be overloaded.