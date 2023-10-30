# Documentation

Documentation can help other people (or future you) understand what your code does. Sometimes your code might use vague function names, or a tricky solution which is not immediately obvious to the untrained eye. To clarify what your intention is, you can add comments throughout your code.

## Annotations

Annotations are best used to further explain what a line of code does, or communicate the intent to the reader.
They are also a good fit for personal notes, for "TODO" markers, or to disable code without having to delete it.

### Single line comments

```
// Anything past the two forward slashes until the next line is considered a comment.
```

### Sectional/Multi line comments

```
/* Anything between these characters is considered a comment. */
```

```
/*  This comment starts on this line,
    goes on throughout the next one,
    and ends after these two characters: */
```

## Hints

_Smelt_ (or other documentation generators) can use documentation hints to automatically generate more in-depth information about your code.
You can give all top-level definitions a documentation hint.

### Hint tags

Here are all available hint tags:

| Name       | Description                                                                                             |
| ---------- | ------------------------------------------------------------------------------------------------------- |
| `\brief`   | A brief overview of what this element does.                                                             |
| `\details` | An in-depth description of what this element does.                                                      |
| `\param`   | What this function parameter does. If there are multiple parameters, these tags are evaluated in order. |
| `\returns` | What this function returns.                                                                             |
| `\code`    | A name reference to a type or function.                                                                 |

### Examples

```
/// \brief      Creates a new \code String instance.
/// \param      The size in bytes.
/// \returns    A \code String instance with a specified size.
String createString(i32 size) { ... }
```

This might render out to something like this:

> ```
> String createString(i32 size)
> ```
>
> Creates a new `String` instance.
>
> Parameters:
>
> -   `i32 size`: The size in bytes.
>
> Returns:
> A `String` instance with a specified size.
