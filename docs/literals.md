# Literals

Literals are concrete and absolute values that can't be modified at run time and are baked into the executable.

There are 5 types of literals:

-   Integer literals
-   Floating point literals
-   Boolean literals
-   Character literals
-   String literals

The next section shows some examples for each literal type.

## Integer literals

> **Note:** By default, attempting to store a value with an integer type that's not large enough to fit the literal will wrap around the number (e.g. if `u8 foo = 256;`, then foo will evaluate to `1`) and results in a warning if this can be detected at compile time.

-   Decimal numbers:
    -   `5`
    -   `-999`
    -   `1_000_000_000`
-   Hexadecimal numbers:
    -   `0xA`
    -   `0xC0FFEE`
-   Binary numbers:
    -   `0b101`
    -   `0b10000001`
    -   `0b1111_1001`

> **Note:** By default, assigning a negative decimal literal to an unsigned integer (`u8`, `u16`, `u32`, `u64` or `usize`) will store the 2's complement of that value (e.g. if `u16 foo = -1;`, then `foo` will evaluate to `0xFFFFFFFF`) and results in a warning if this can be detected at compile time.

## Floating point literals

-   Single precision numbers:
    -   `1.0f`
    -   `-23423.26F`
-   Double precision numbers:
    -   `3.14159`
    -   `12345.6789`

## Boolean literals

-   `true`
-   `false`

## Character literals

-   Letters, symbols and numbers:
    -   `'A'`
    -   `'+'`
    -   `'4`
-   Escape sequences:
    -   `'\n'`
    -   `'\n'`
    -   `'\t'`
    -   `'\x31'`
    -   `'\0'`

## String literals

-   Regular strings:
    -   `"Hello, world!"`
    -   `"Very awesome\ttext."`
-   Raw strings:
    -   `"""Everything in here is stored "exactly" like it's written in the file, even \n or \t are ignored."""`
