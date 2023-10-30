# Operators

Operators take a left hand and right hand input and combine both to produce a new value.
Almost all of them can be [overloaded](functions.md#overloading) by the user.

## Arithmetic

| Symbol | Description    |
| ------ | -------------- |
| `+`    | Addition       |
| `-`    | Subtraction    |
| `*`    | Multiplication |
| `/`    | Division       |
| `%`    | Modulo         |
| `**`   | Exponent       |

## Binary

| Symbol | Description          |
| ------ | -------------------- |
| `\|`   | Bitwise Or           |
| `&`    | Bitwise And          |
| `^`    | Bitwise Exclusive Or |
| `<<`   | Bitwise Shift Left   |
| `>>`   | Bitwise Shift Right  |
| `!`    | Binary Not           |

> All arithmetic and binary operators can be combined with the assignment operator:
>
> ```
> myInt *= 5;  // myInt = myInt * 5;
> myInt <<= 3; // myInt = myInt << 3;
> ```

## Logical

| Symbol | Description        |
| ------ | ------------------ |
| `\|\|` | Or                 |
| `&&`   | And                |
| `==`   | Equal              |
| `!=`   | Not Equal          |
| `<`    | Less Than          |
| `<=`   | Less Than Or Equal |
| `>`    | More Than          |
| `>=`   | More Than Or Equal |

## Other

| Symbol | Description                   |
| ------ | ----------------------------- |
| `=`    | Assignment (Not overloadable) |
| `[]`   | Element Access                |
| `()`   | Type Conversion               |
