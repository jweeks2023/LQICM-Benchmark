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
- A general understanding of how to use a terminal

## How To Use:
### Set Up
1. Download/clone the repo to the desired location.
2. If desired, change `ITERATIONS` or `NEATDISPLAY` in `benchmark.c` to desired values.
4. Save your code.
5. In your terminal, naviagte to the `LQICM-Benchmark` folder. (Use `cd`)
6. Compile your code using clang in the terminal. I recommend using this line: `clang-15 benchmark.c -O0 -o benchmark -lm`.
### Inserting Code
1. In your file explorer, navigate to the `CodeToTest` folder.
2. Insert the code you want to test as .c files in the folder
    - Note: Make sure your code compiles and runs as expected before attempting to benchmark it. Failure to do so may cause inaccurate benchmark results.
### Running the Benchmark
1. Run the benchmark using the following command: `./benchmark`.
2. See output file in the `Outputs` folder for results.
### Reviewing Results
- Output files will be in the format `output YYYY-MM-DD HHMMSS.txt`.
- Data will be in seconds, with 6 decimals of precision.

## Some Notes
If you want to change the number of times each file is benchmarked, change `ITERATIONS`.
If you want your benchmark results to be output in a table, set `NEATDISPLAY` to `true`.
