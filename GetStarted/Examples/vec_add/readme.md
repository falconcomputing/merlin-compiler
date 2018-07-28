## Readme: Vector Addition Example for MerlinCC
Copyright (C) 2018 Falcon Computing Solutions, Inc. - All rights reserved.

Description:
This example shows how to effectively use the ACCEL 'parallel' pragma to 
improve the overall performance of your kernel. 

The operation we are targeting is an addition of vectors 'a' and 'b' and a 
constant value 'inc', where the result is stored in a vector 'c'.
The reference vec_add function implementation is in vec_add.cpp. In order to 
accelerate the vec_add function we insert ACCEL pragmas to instruct MerlinCC 
of the design intentions. The modified file is vec_add_kernel.cpp and this is 
what will be compiled by MerlinCC. The main function executes the reference 
vec_add function and vec_add_kernel function and compares the outputs for 
functional correctness. 

You could simply compile the original vec_add function with MerlinCC and 
generate a kernel binary for your target FPGA device. However, to achieve 
better performance, this design can be easily parallelized (unrolled). If we
were to fully unroll the vec_add loop using the ACCEL 'parallel' pragma it 
would result in 10000 vec add operations in parallel which might be too many 
to practically fit in the FPGA. Instead we parallelize a subset of operations 
by applying the ACCEL 'parallel' pragma with the 'factor' option. MerlinCC
will then automatically tile the loop by inserting a subloop which will then 
be unrolled. In this example we set the factor to 16 by default, but you can 
achieve more parallelization by increasing this number at the expense of more 
FPGA resource utilization and potentially slower frequency of operation.
```
Directory Structure:
.
├── build
│   ├── Makefile
├── include
│   └── vec_add.h
├── readme.md
└── src
    ├── main.cpp
    └── vec_add_kernel.cpp
```
Usage:
- Goto the build directory:
  $ cd build

- View the Makefile and modify the VENDOR/DEVICE variables and target platform per your 
  requirements. If using AWS F1, modify the S3_OPT variable as well:
  $ vi Make (or use whatever your fav editor is)

- List all the make targets for your reference:
  $ make

- Compile code for CPU (host) execution only into an executable named 'test' 
  and run it to verify functionality of the modified kernel code. 
  $ make run

- Compile the kernel code to accelerate using MerlinCC. This will generate a
  Merlin intermediate object file with a .mco extension, the Merlin lib*.so
  file, and a __merlin*.h file.
  $ make mcc_acc

- Generate the simulation binary of the kernel, recompile host code to use the 
  kernel binary file into an executable named 'test_acc', and run it on the 
  host to verify functionality.
  After running the executable, you can view profiling information in 
  profile.mon (Intel) or sdaaccel_profile_summary.html (Xilinx).
  $ make mcc_runsim

- Generate an estimate of the FPGA resources.
  $ make mcc_estimate

- Generate the FPGA hardware binary of the kernel (Note: this can take hours).
  $ make mcc_bitgen

- Test functionality on the FPGA itself by running the 'test_acc' executable
  with the FPGA binary.
  After running the executable, you can view profiling information in 
  profile.mon (Intel) or sdaaccel_profile_summary.html (Xilinx).
  $ make mcc_runaccexe

Notes:
- The binary file extension for Intel is .aocx and for Xilinx is .xclbin 
- You can view reports at the various stages of the flow in the merlin.log

