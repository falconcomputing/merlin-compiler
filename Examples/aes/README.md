**OVERVIEW**<br>
Advanced Encryption Standard (AES) is a symmetric block cipher chosen by the U.S. government to protect classified information and is implemented in software and hardware throughout the world to encrypt sensitive data.

**DOWLOAD THE REPOSITORY**<br>
```
git clone https://github.com/falconcomputing/merlin-compiler.git
cd merlin-compiler/Examples/aes
```

**FILE HIERARCHY**<br>
<TABLE>
 <TR><TH>Folder</TH><TH>Sub-folder</TH><TH>Description</TH></TR>
 <TR><TD>aes</TD><TD>     </TD><TD>Example top folder</TD></TR>
 <TR><TD>      </TD><TD>build</TD><TD>Contains subfolders and Makefile(s) required to compile for different targets</TD></TR>
 <TR><TD>      </TD><TD>data</TD><TD>data to test the correctness of the program</TD></TR>
 <TR><TD>      </TD><TD>Include</TD><TD>.h  header files</TD></TR>
 <TR><TD>      </TD><TD>src</TD><TD>.c, .cpp source files</TD></TR>
 <TR><TD>common</TD></TD>   <TD><TD>common to all Merlin examples</TD></TR>
</TABLE>

**COMPILE and RUN on AWS**<br>
In this section, we will provide a summary of the steps required to compile and deply this on F1. For a more detailed version of these instructions, please visit this: <a href="COMPILE.md">Compile on AWS with Merlin</a>.

Step1: Compile for CPU only target (no acceleration):
```
make cpu run
```

Step 2: Record the program execution time for future comparison with the accelerated version.

Step 3: Compile FPGA binaries:
```
make xilinx mcc_bitgen
```

step 3: Prepare .xclbin kernel binary for F1 instance
For more details, please visit this: <<a href="COMPILE.md">Compile on AWS with Merlin</a>***

Step 4: Compile the host app
```
make xilinx mcc_accexe
```

Step 5: Package files to deply on F1 instance
```
make xilinx mcc_pkg
```

Step 6: Copy the files from compile host to AWS F1 instance:
```
scp build/xilinx_mo/aesapp_pkg.tar.gz centos@<F1_instance_ip_address>:~/
```

Step 7: On the AWS F1 instance:
```
tar xvzf aesapp_pkg.tar.gz 
cd aesapp_pkg
make mcc_runhw
```

Step 8: Record the accelerate program execution time 

Step 9: Compare to the CPU execution recorded in step #2 

***For a more detailed version of these instructions, please visit this: <a href="../../On-Cloud/AWS/COMPILE.md">Compile on AWS with Merlin</a>.***
