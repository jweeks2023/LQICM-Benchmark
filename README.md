# LQICM-Benchmark
A repo containing the benchmark program used in the LQICM senior capstone project. THIS IS A WIP!!!


## Contents
- README.md: This File!
- benchmark.c: The benchmarking code in question.

## Prerequisites
- A computer with LLVM installed (Linux Required?)
- Code that you want to benchmark

## How To Use:
1. Download/clone the repo to the desired location.
2. Open benchmark.c and create a new method within the file that contains the code you want to test (make a new method per code block).
3. Call your method on the line that has the comment `//change this method to whatever method you're using`.
4. Save your code.
5. Compile your code using clang in the terminal. I recommend using this line: `clang-15 benchmark.c -O0 -o benchmark -lm`.
6. Run your compiled code. `./benchmark`.

## Extras
If you want to change the number of iterations your code sample runs for, change `samples`.
If you want your code to display in a table, set `neatDisplay` to `true`.
