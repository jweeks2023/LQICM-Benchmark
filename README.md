# LQICM-Benchmark
A repo containing the benchmark program used in the LQICM senior capstone project. THIS IS A WIP!!!

## To Do!
- ~~Create a way to bulk measure files~~
- ~~Output results to a .txt file~~
- ~~Comment and clean up code~~

## Contents
- README.md: This File!
- benchmark.c: The benchmarking code in question.
- CodeToTest Folder: This is where you put your code to test (crazy ik)
- Outputs Folder: This is where the results of the benchmark are output

## Prerequisites
- A computer with LLVM installed (Linux Required?)
- Code that you want to benchmark

## How To Use:
1. Download/clone the repo to the desired location.
2. If desired, change `ITERATIONS` or `NEATDISPLAY` in `benchmark.c` to desired values.
4. Save your code.
5. Compile your code using clang in the terminal. I recommend using this line: `clang-15 benchmark.c -O0 -o benchmark -lm`.
6. Run your compiled code. `./benchmark`.
7. See output file in the `Outputs` folder for results.

## Extras
If you want to change the number of iterations your code sample runs for, change `ITERATIONS`.
If you want your code to display in a table, set `NEATDISPLAY` to `true`.
