# Reverse Polish Notation Solver

This project provides a solution for evaluating expressions in Reverse Polish Notation (RPN) using custom data structures implemented in C++.

## Overview

Reverse Polish Notation (RPN) is a mathematical notation where every operator follows all of its operands. This project offers a way to evaluate RPN expressions efficiently.

## Features

- Support for basic arithmetic operations: addition, subtraction, multiplication, division
- Custom implementation of data structures:
  - **MyString**: A custom string class
  - **Vector/Stack**: A dynamic array-based stack implementation
  - **LinkedListStack**: A stack implemented using a linked list
- Object-oriented design for modularity and extensibility

## Usage

To use this project, follow these steps:

1. Clone the repository to your local machine.
2. Compile the source code using a C++ compiler. In VS Code, you can open the terminal and type `g++ main.cpp string.cpp -o a.out` if you have the g++ compiler installed (feel free to use other compilers like CLANG).
3. Include the necessary header files in your project.
4. Create RPN expressions ending with a `.` sign and use the provided functions to evaluate them.

## Compiling

Type this in terminal to create your binary (`.out` extension in linux and `.exe` extension in windows):
```
g++ main.cpp string.cpp
./a.out < ./tests/test.txt
```

## Example

### Input
```
4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .
2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .
N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .
IF ( ( 6 + 8 ) , ( 4 / 2 ) , MIN ( 8 , 2 , 1 , 0 , 3 ) ) * 2 * 6 / N ( 3 ) .
```

### Output
```
100  1  34  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6
MAX3 2 34 1 100
MIN4 77 35 36 66 80 34 100
MIN6 60 50 35 80 34 100
34

2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +
* 5 6 1 100 2
+ 2 30 1 100 2
MAX3 2 32 1 100 2
MIN4 77 35 36 66 80 32 100 2
MIN6 60 50 35 80 32 100 2
* 3 32 2
+ 96 2
98

400  N  11  3  2  *  -  2  /  +  200  N  N  +
N 400
* 2 3 11 -400
- 6 11 -400
/ 2 5 -400
+ 2 -400
N 200 -398
N -200 -398
+ 200 -398
-198

6  8  +  4  2  /  8  2  1  0  3  MIN5  IF  2  *  6  *  3  N  /
+ 8 6
/ 2 4 14
MIN5 3 0 1 2 8 2 14
IF 0 2 14
* 2 2
* 6 4
N 3 24
/ -3 24
-8
```
