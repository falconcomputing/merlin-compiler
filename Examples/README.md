Examples
<TABLE>
   <TR>
      <TD>Name</TD>
      <TD>Category</TD>
      <TD>Target FPGA</TD>
   </TR>
   <TR>
      <TD>Vector Add</TD>
      <TD>Tutorial</TD>
      <TD>AWS F1/Xilinx</TD>
   </TR>
   <TR>
      <TD>Dot Product</TD>
      <TD>Linear Algebra</TD>
      <TD>AWS F1/Xilinx</TD>
   </TR>
   <TR>
      <TD>AES</TD>
      <TD>Security</TD>
      <TD>AWS F1/Xilinx</TD>
   </TR>                                                                             
   <TR>
      <TD>BlackScholes Asian Options</TD>                                            
      <TD>Financial</TD>                                                             
      <TD>AWS F1/Xilinx</TD> 
   </TR>
</TABLE>

------------------------------------

**How to compile with Merlin**<br>
In this tutorial, we will use a simple design “vector_add” to illustrate how to compile with Merlin. These steps can be applied to all the design examples.

**Get the Example code**<br>
```
git clone https://github.com/falconcomputing/merlin-compiler.git
cd merlin-compiler/Examples/vectoradd/build/xilinx_mo
```

**View the available make targets**<br>
```
make 

**************************************************************************************
* Merlin Compiler Makefile                                                           *
* Copyright (C) 2015-2019 Falcon Computing Solutions, Inc. - All rights reserved.    *
*                                                                                    *
* Usage: make <target>                                                               *
*                                                                                    *
* Available targets:                                                                 *
*          run - Compile and run executable on CPU without Acceleration (cpu only)   *
*   mcc_runsim - Generate kernel binary for simulation on CPU and run it             *
* mcc_estimate - Get resource and performance estimates                              *
*   mcc_bitgen - Generate kernel binary for Acceleration Platform                    *
*    mcc_runhw - Run executable on Host CPU and accelerated kernel on platform HW    *
*   mcc_afigen - Generate AFI for AWS F1 FPGA (AWS F1 users)                         *
*   mcc_accexe - compile accelerated executable on CPU and link with merlin runtime  *
*      mcc_pkg - Package all necessary files for running accelerated application     *
*        clean - Remove all output products (except for bitgen outputs)              *
**************************************************************************************
```
***Run your code on CPU***<br>
```
make run
```

***Compile the kernel and run CPU emulation***
```
make mcc_runsim
```

***Compile the kernel and estimate the performance and resource utilization***
```
make mcc_estimate
```

***Compile the kernel and generate the FPGA binary (bitstream)***
Generate the  .xclbin file
```
make mcc_bitgen
```

***Compile your host executable***
Next step is to generate the host binary and library files:
```
make mcc_accexe
```

Note that these examples are set up using AWS F1 platform. To use another platform, you just need to modify the variable *DEVICE* in Makefile. For example, to use Xilinx Alveo U250, you can set the following:  
```
DEVICE=xilinx_u250_xdma_201830_1
```
