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

. Running *HALK* with no arguments allows one to lex(?) arbitrary text through stdin. An 
example session is displayed below:

```text
$ halk
:str:var = "Hello, World";
[==] HLKT: test passed: src/main.c/main/18
[==] source gotten
[==] source: :str:var = "Hello, World";

[==] HLKT: test passed: src/main.c/main/24
[==] preprocessor created
[==] pre-processed source: :str:var="Hello, World";
[==] HLKT: test passed: src/main.c/main/34
[==] preprocessor ran
[==] HLKT: test passed: src/main.c/main/39
[==] HLKT: test passed: src/main.c/main/40
[==] lexer created
[==] token/t=9	/v=str
[==] token/t=9	/v=var
[==] token/t=4	/v==
[==] token/t=2	/v=Hello, World
[==] token/t=3	/v=;
[==] lexer ran
[==] HLKT: all 5 tests passed
```

# Syntax

*HALK* is a **dubiously-typed**, **vaguely-functional**, **interpreted**  programming language, 
with syntax designed to be as **minimal** and **consistent** as possible. Note that all syntax 
described is liable to sudden and violent change.

Example programs can be found [here](../tree/examples).

- [x] Preprocessor
- [x] Lexer
- [x] Abstract Syntax Tree
- [ ] Parser
- [ ] Doer
- [ ] ?? profit ??
