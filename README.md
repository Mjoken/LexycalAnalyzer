# Lexical Analyzer for C++ Language Constructs

This project implements a lexical analyzer in C++ for a subset of the C++ language. The lexer supports the following language elements:

- Keywords: `if`, `then`, `else`, `int`, `float`
- Delimiters: Spaces
- Comments: `//`, `/**/`

## Usage

To use the lexical analyzer, follow these steps:

1. Compile the source code using a C++ compiler.
2. Run the executable with the input file as an argument.

## Input Format
The input file should contain C++ code that needs to be analyzed. The lexer will tokenize the input and print the tokens to the console.

## Output Format
The lexer will output each token along with its type. Tokens are printed in the format <TOKEN_TYPE: TOKEN_VALUE>.

## Example:
$ g++ lexer.cpp -o lexer
$ ./lexer input.cpp

Example
For the input file input.cpp containing:
    if (x < 10) {
        // Increment x
        x++;
    } else {
        // Reset x
        x = 0;
    }
