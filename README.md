# LQICM-Benchmark
A repo containing the benchmark program used in the Loop Quasi-Invariant Code Motion (LQICM) senior capstone project.

## Contents
- README.md: This File!
- benchmark.c: The benchmarking code in question.
- CodeToTest Folder: Destination folder for all test code
- Outputs Folder: Destination folder for outputted benchmark results

## Prerequisites
- A computer/virtual machine running Linux
    - Note: Further testing needed on other operating systems before I can confirm that it's functional on Windows/Mac
- A C compiler (LLVM or GCC recommended)
- Code that you want to benchmark

## How To Use:
### Set Up
1. Download/clone the repo to the desired location.
2. Open the `LQICM-Benchmark` folder to make sure all the files from the Contents section are there.
3. If desired, open the `benchmark.c` file in a text editor and change the parameters at the top of the program.
    - `ITERATIONS` - Number of times each file is benchmarked. (default: 20)
    - `NEATDISPLAY` - Determines whether the benchmark data is output in a table. true = table, false = no table. (default: true)
    - `COMPILER` - Specifies what C compiler you're using. (default: "clang-15")
    - `COMPILERPATH` - Specifies the filepath for the compiler above. (default: "../../../usr/bin/")
    - `INPUTFOLDER` - Specifies the filepath for the folder that will contain the C files that you want to benchmark (default: "./CodeToTest/")
    - `OUTPUTFOLDER` - Specifies the filepath for the folder that will contain all the output files that is generated by the benchmark (default: "./Outputs/")
    - `OPTLEVEL` - Specifies what optimization level your compiler will apply to the files being benchmarked (default: O0)
        - For more information on optimization levels, see [this link](https://clang.llvm.org/docs/CommandGuide/clang.html#cmdoption-o0)
4. Compile `benchmark.c`.
    - Note: We recommend using clang since it comes with LLVM and is more efficient than gcc. Ultimately, you can use any C compiler you like.
    - Example using clang-15: `clang-15 benchmark.c -o benchmark -lm`.
### Inserting Code
1. In your file explorer, navigate to the `CodeToTest` folder.
2. Insert your own test code as .c files in the folder. Each C file will be timed separately, and will output in separate output files.
    - Note: Make sure your code compiles and runs as expected before attempting to benchmark it. Failure to do so may cause inaccurate benchmark results. An example file is provided in the `CodeToTest` folder.
### Running the Benchmark
1. Make sure you're in the `Benchmark` folder and run the benchmark using the following command: `./benchmark`.
2. View results in the `Outputs` folder.
### Reviewing Results
- Output files will be in the format `output YYYY-MM-DD HHMMSS.txt`. The title of the C program that is timed is contained at the top of the file.
- Data will be in seconds, with 6 decimals of precision.
### An Example Following The Steps Above
1. Clone the repository:
```
git clone https://github.com/jweeks2023/LQICM-Benchmark.git
```
2. Navigate into the folder and check contents:
```
cd LQICM-Benchmark
dir
```
Expected output: 
```
>>> CodeToTest  LICENSE.md  Outputs  README.md  benchmark  benchmark.c
```

3. Open file in text editor and chang parameters
```C
//In the benchmark.c file

#define ITERATIONS 20					//number of times each file is benchmarked (default: 20)
#define NEATDISPLAY true				//sets if results will be output in a table or plain numbers; true = table, false = plain (default: true)
#define COMPILER "clang-15"			    //specifies what compiler version you're using (default: clang-15)
#define COMPILERPATH "../../../usr/bin/"	//filepath of the compiler defined above (default: "../../../usr/bin/")
#define INPUTFOLDER "./CodeToTest/"		//filepath for folder containing files to test (default: " ./CodeToTest/")
#define OUTPUTFOLDER "./Outputs/"		//filepath for folder containing results of benchmark (default: "./Outputs/")
#define OPTLEVEL "O0"				//the level of optimization the code being benchmarked is (default: O0)
```
4. Compile benchmark.c
```
clang-15 benchmark.c -o benchmark -lm
```
5. Run the executable
```
./benchmark
```
Expected Output from Console:
```
>>> Running benchmark for demo.c...Done!√
>>> Check the "Outputs" folder for results.
```
Expected Output in File:

When `NEATDISPLAY` is `true`:
```
//In the output file

Benchmark Results of demo.c
Iteration Runtimes:
 ID|Runtime (sec)
---|-------------
  1|0.455837
  2|0.440500
  3|0.447806
  4|0.445283
  5|0.446175
  6|0.444677
  7|0.448382
  8|0.441302
  9|0.442823
 10|0.456849
 11|0.441625
 12|0.450338
 13|0.438839
 14|0.453270
 15|0.447044
 16|0.451858
 17|0.461983
 18|0.462734
 19|0.449385
 20|0.441156
Mean runtime: 0.448393
Median runtime: 0.448094
```
When `NEATDISPLAY` is `false`:
```
//In the output file

Benchmark Results of demo.c
Iteration Runtimes:
0.455837
0.440500
0.447806
0.445283
0.446175
0.444677
0.448382
0.441302
0.442823
0.456849
0.441625
0.450338
0.438839
0.453270
0.447044
0.451858
0.461983
0.462734
0.449385
0.441156
Mean runtime: 0.448393
Median runtime: 0.448094
```

## Common Bugs
`sh: 1: [OBJECT OR FILE PATH]: not found` - Most likely the compilation of the C file being benchmark failed. Check the `COMPILERPATH` parameter to make sure it points to the same folder `COMPILER` exists in.

Any error message that displays repeatedly in rapid succession - This is most likely an error with your C file. Make sure you can compile and run your code through your compiler before putting it in the `CodeToTest` folder.

`Command '[COMPILER]' not found, but can be installed with:` - This means that you are referencing a compiler that you do not have installed. This issue is common when you install LLVM, as many commands require the command followed by `-[VERSION NUMBER]`. This is why the default value for `COMPILER` is `clang-15`. Please verify you've installed a C compiler and that you are referencing the correct version in the command.

Created by Jason Weeks, Justice Howley, and Ian Yelle, 2023 
