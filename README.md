# HALK

<img src="./res/HALK_FINAL.svg" width="350" align="right">

*HALK* seeks to be a language.

I seek to fulfill its wishes.

As of yet, *HALK* is nothing.

As of yet, we are safe.

# Installation

As you have read these words, you are to install *HALK*.

1. Clone *HALK* to a computer.
2. `sudo make install`.

If you wish to remove all *HALK*-related items from your life, you can try `make clean`, followed 
by `sudo make uninstall`.

# Usage

The *HALK* binary is placed in `/usr/local/bin`. Assuming that is in your PATH, one must simply

```shell
$ halk examples/simple.halk
```

while in this directory, or change the argument to any valid file path. Simply running *HALK* with no arguments allows one
to lex(?) arbitrary text from the command line. An example session is displayed below:

```shell
$ halk
> :str:var = 'Hello, World.';
> ^D
[==] lexer created
[==] BEGIN INPUT
:str:var = 'Hello, World.';
[==] END INPUT
[==] token type: [TOKEN_DEF_TAG]    token value: [str]
[==] token type: [TOKEN_DEF_TAG]    token value: [var]
[==] token type: [TOKEN_DEF_SET]    token value: [=]
[==] token type: [TOKEN_PRIM_STR]      token value: [Hello, World.]
[==] token type: [TOKEN_EXPR_END]      token value: [;]
[==] token type: [TOKEN_EOF]     token value: []
[==] source file closed
```

# Syntax

*HALK* is a **dubiously-typed**, **vaguely-functional**, **interpreted**  programming language, with syntax designed to be as
**minimal** and **consistent** as possible.
Note that all syntax described is liable to sudden and violent change.

Example programs can be found [here](examples/).

***HALK*** **progress:** 20%

- [x] Lexer
- [x] Abstract Syntax Tree
- [ ] Preprocessor
- [ ] Parser
- [ ] Doer
- [ ] ?? profit ??
