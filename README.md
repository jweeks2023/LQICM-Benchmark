# LQICM-Benchmark
A repo containing the benchmark program used in the LQICM senior capstone project.

## Contents
- README.md: This File!
- benchmark.c: The benchmarking code in question.
- CodeToTest Folder: This is where you put your code to test
- Outputs Folder: This is where the results of the benchmark are output

## Prerequisites
- A computer with LLVM installed (Linux Required?)
- Code that you want to benchmark
- A general understanding of how to use a terminal

## How To Use:
### Set Up
1. Download/clone the repo to the desired location.
2. If desired, change `ITERATIONS` or `NEATDISPLAY` in `benchmark.c` to desired values.
4. Save `benchmark.c` if any changes were made.
5. If not already there, naviagte to the `LQICM-Benchmark` folder in the terminal window. (Use `cd`)
6. Compile `benchmark.c`.
    - Note: We recommend using clang since it comes with LLVM and is more efficient than gcc. Ultimately, you can use any C compiler you like.
    - Example using clang-15 with no optimization: `clang-15 benchmark.c -O0 -o benchmark -lm`.
### Inserting Code
1. In your file explorer, navigate to the `CodeToTest` folder.
2. Insert your own test code as .c files in the folder.
    - Note: Make sure your code compiles and runs as expected before attempting to benchmark it. Failure to do so may cause inaccurate benchmark results. An example file is provided in the `CodeToTest` folder.
### Running the Benchmark
1. Run the benchmark using the following command: `./benchmark`.
2. See output file in the `Outputs` folder for results.
### Reviewing Results
- Output files will be in the format `output YYYY-MM-DD HHMMSS.txt`.
- Data will be in seconds, with 6 decimals of precision.

## Some Notes
If you want to change the number of times each file is benchmarked, change `ITERATIONS`.
If you want your benchmark results to be output in a table, set `NEATDISPLAY` to `true`.

Created by Jason Weeks, Justice Howley, and Ian Yelle, 2023 
