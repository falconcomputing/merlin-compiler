<table style="width:100%">
  <tr>
    <th width="100%" colspan="6"><h2>Merlin on AWS</h2></th>
  </tr>
  <tr>
    <td width="20%" align="center"><b>Background</b></td>
    <td width="20%" align="center"><a href="PREREQUISITES.md">Prerequisites</a></td> 
    <td width="20%" align="center"><a href="COMPILE.md">Compile on AWS with Merlin</a></td> 
    <td width="20%" align="center"><a href="DEPLOY.md">Deploy on F1</a></td>
  </tr>
</table>

------------------------------------
**Merlin Compiler on AWS**<br>
Amazon AWS F1 instances has FPGA boards.  The Merlin Compiler is available on the AWS marketplace. It enables software developers to be able to compile their applications for FPGA acceleration without FPGA expertise. Merlin Compiler takes C/C++ code as an input and generates an executable that includes the CPU host-code & the FPGA bitstream . By abstracting all the hardware design details away from the software developers, Merlin provides an easier alternative to leverage FPGAs hosted on AWS F1

**AWS F1 Background**<br>
The architecture of the AWS F1 platform and the SDAccel development flow are pictured below:


![](../../images/f1_platform.png)
 
1.	Amazon EC2 F1 is a compute instance combining Intel CPUs with Xilinx FPGAs. The FPGAs are programmed with custom accelerators which can accelerate complex workloads up to 100x when compared with servers that use CPUs alone.

2.	An F1 application consists of an x86 executable for the host application and an FPGA binary (also referred to as Amazon FPGA Image or AFI) for the custom hardware accelerators. Communication and data movement between the host application and the accelerators are automatically managed by the XRT runtime.

3.	Software Defined Accelerator Development- SDAccel is the development environment used to create applications accelerated on the F1 instance. It comes with a fully fledged IDE, x86 and FPGA compilers, profiling and debugging tools.

4.	Typically with SDAccel, the CPU code would have to be developed independently of the code (kernels) that would be deployed on the FPGA. Merlin accepts single source in C/C++ & generates both the executable for the CPU (host) as well as the FPGA bitstream.
<br>
<br>
Start the next module: <a href="PREREQUISITES.md">Prerequisites</a>
