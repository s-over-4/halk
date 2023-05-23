# The HALK Programming Language

*version 0.0.1*

*2023-05-22*

# Syntax

## Definitions

HALK has no special definition keyword. When a keyword that has not been defined is called, the
interpreter will assume the user is defining a new variable. Definitions have 3 major components:

1. The **Definition Tags**
2. The **Definition Args**
3. The **Definition Value**

### Definition Tags

Tags help describe the variable before it is given a value. This ensures it will be handled properly
in the future. A variable definition can have any number of tags, but the most important one by far
is the type.

```halk
int:n = 5;
```

The type is always the first tag, and is terminated by a colon `:` character. Following the type,
the second most important tag is the name, in this case `n`. The name tag is always the last. In
between these, there can be any number of tags.

```halk
int:mut:var = 4;
int:imut:var2 = 4;
```

In this case, `var` has the `mut` tag while `var2` has the `imut` tag. These indicate the  
mutabillity of a variable. When not specified, the interpreter will assume `imut`.

## Calls

# Data Structures

## Namespaces

## Structs

# Logic & Program Flow

## If / Else

## For / While

## Cond

# Style
