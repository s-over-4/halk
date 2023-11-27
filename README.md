# Installation

As you have read these words, you are to install HALK.

```
$ sudo make install
```

If you wish to remove all HALK-related items from your life, you can try

```
$ sudo make uninstall
```

As of 82e7599, HALK has been tested on both Linux and MacOS.

# Usage

One must simply

```
$ halk examples/simple.halk
```

. This will print out the token and AST representations of the given text. Running HALK 
without an argument allows one to pass in text through stdin. An example session is transcribed
below:

```
$ halk
:int:n=42;
[==] HLKT: test passed: src/main.c/main/20
[==] source gotten
[==] source: :int:n=42;
[==] HLKT: test passed: src/main.c/main/26
[==] preprocessor created
[==] pre-processed source: :int:n=42;
[==] HLKT: test passed: src/main.c/main/36
[==] preprocessor ran
[==] HLKT: test passed: src/main.c/main/41
[==] HLKT: test passed: src/main.c/main/42
[==] lexer created
[==] token/t=9	/v=int
[==] token/t=9	/v=n
[==] token/t=4	/v==
[==] token/t=17	/v=42
[==] token/t=3	/v=;
[==] lexer ran
[block]
val:
 [expression]
 val:
  [def]
  tag:
   [tag]
   val:
    int
   nxt:
    [tag]
    val:
     n
    nxt:
     NULL
  arg:
   NULL
  val:
   [expression]
   val:
    [lint]
    val:
     42
nxt:
 NULL
```

# About

HALK is a **dubiously-typed**, **vaguely-functional**, **interpreted**  programming language,
with syntax designed to be as **minimal** and **consistent** as possible. Note that all syntax
described is liable to sudden and violent change.

Example programs can be found in the examples directory.

# Progress

- [x] Preprocessor
- [x] Lexer
- [x] Abstract Syntax Tree
- [~] Parser
- [ ] Doer
- [ ] ?? profit ??
