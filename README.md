# HALK

*HALK* seeks to be a language.

I seek to fulfill its wishes.

As of yet, *HALK* is nothing.

As of yet, we are safe.

# Installation

As you have read these words, you are to install *HALK*.

1. Clone *HALK* to a computer.
2. `sudo make install`.

If you wish to remove all *HALK*-related items from your life, you can try `sudo make clean`.

# Usage

Seeing as you have installed *HALK*, it only makes sense that you should attempt to make use of it.
You are mistaken.
Usage of *HALK* is not yet a feature of *HALK*.
One can only hope this feature will be added in the future.


# Syntax

*HALK* is a **dubiously-typed**, **procedural**, **interpreted**  programming language. 
Note that all syntax described is liable to sudden and violent change.

```HALK
[comments in square brackets]

[preprocessor directives]
#INCLUDE 'math.halk';                                    [looks for a 'math.halk' file in the cwd, then ~/halk/include]
#INCLUDE 'io' AS '';                                     [bring everything in 'io' into global scope]


let.hello -> 'hello, ';                                  [variables must be given a value at declaration]

let.PI => math/PI;                                       [namespaces are accessed with a '/']
                                                         [constants are denoted with a '=>']

fn.greeting,to -> {                                      [functions defined with: `fn.<name>,<argument>,..., -> {<body>};`] 
   let.message -> strcat.hello,to;                       [functions are right-associative]

   stdo.message;                                         [since 'io' was brought into global scope, we
                                                         do not prefix it with a namespace/]
};

fn.sum_all._ -> {                                        [variadic functions are possible with the reserved '_' argument,
                                                         which is treated as an array]
   return.foldl.+,0,_;  
};

fn.fibonacci.n -> {
   if.or.(num=?.n, 0), (num=?.n, 1) -> {                 [functions ending in '?' should be predicates]
      return.1;
   };
   return.+.(fibonacci. -.n, 1), (fibonacci. -.n, 2);    [parens can be used to group function application]
};

fn.main -> {   [where our code will begin executing]
   greeting.[comments can be placed *anywhere*]"world.";
   exit.0;                                               [exit with code 0 for success]
};
```

***HALK*** **progress:** 20%

- [x] Lexer
- [ ] Abstract Syntax Tree
- [ ] Parser
- [ ] Doer
- [ ] ?? profit ??
