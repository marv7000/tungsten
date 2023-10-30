# Structs

Sometimes, you want to store more than one value in a variable. A `struct` can store an arbitrary amount of values in one type, though it must contain at least one field.

## Syntax

```
struct <Name>
{
    <Fields>
}
```

A `struct` must contain at least one field.

## Fields

Fields are defined by providing a type, field name and optionally, a literal value.
If no literal is given, the variable will be assigned the default value of a type (see [`default` keyword](default.md)).

```
Type fieldName;
```

or

```
Type fieldName = ...;
```

## Methods

Methods are defined by providing a return type, a method name and optionally, parameters.
By default, all fields and methods are internal to the struct. To make fields accessible to any calling functions, add a modifier

## Operators

A struct may contain custom [arithmetic operators](operators.md#arithmetic). This is done by

## Casting

A struct can have user defined conversions to other types. Let `OutType` be the target type, `InType` the input type and `foo` the name of the input variable. Define a conversion between the two types like this:

```
OutType operator(InType foo) { }
```

## Example

```
struct Person
{
    str name;
    u8 age = 0;

    u8 getAge()
    {
        return age;
    }
}
```
