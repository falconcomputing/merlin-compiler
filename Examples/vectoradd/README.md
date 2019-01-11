## Readme: Vector Addition Example for MerlinCC
Copyright (C) 2019 Falcon Computing Solutions, Inc. - All rights reserved.

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

**DOWLOAD THE EXAMPLE**<br>
```
git clone https://github.com/falconcomputing/merlin-compiler.git
cd merlin-compiler/Examples/vectoradd
```

**FILE HIERARCHY**<br>
<TABLE>
 <TR><TH>Folder</TH><TH>Sub-folder</TH><TH>Description</TH></TR>
 <TR><TD>vectoradd</TD><TD>     </TD><TD>Example top folder</TD></TR>
 <TR><TD>      </TD><TD>build</TD><TD>Contains subfolders and Makefile(s) required to compile for different targets</TD></TR>
 <TR><TD>      </TD><TD>data</TD><TD>data to test the correctness of the program</TD></TR>
 <TR><TD>      </TD><TD>Include</TD><TD>.h  header files</TD></TR>
 <TR><TD>      </TD><TD>src</TD><TD>.c, .cpp source files</TD></TR>
 <TR><TD>common</TD></TD>   <TD><TD>common to all Merlin examples</TD></TR>
</TABLE>
 
<br>

**COMPILE and RUN on AWS**<br>
Fore detailed step-by-step instruction, please visit: <a href="COMPILE.md">Compile on AWS with Merlin</a>.
