# Installation

As you have read these words, you are to install *HALK*.

```
$ sudo make install
```

If you wish to remove all *HALK*-related items from your life, you can try

```
$ sudo make uninstall
```

# Usage

One must simply

```
$ halk examples/simple.halk
```

. Simply running *HALK* with no arguments allows one to send arbitrary text.
An example session is displayed below:

```
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

Example programs can be found [here](tree/examples).

- [x] Preprocessor
- [ ] Lexer
- [ ] Abstract Syntax Tree
- [ ] Parser
- [ ] Doer
- [ ] ?? profit ??
