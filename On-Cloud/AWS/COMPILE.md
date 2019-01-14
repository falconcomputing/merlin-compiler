<table style="width:100%">
  <tr>
    <th width="100%" colspan="6"><h2>Merlin on AWS</h2></th>
  </tr>
  <tr>
    <td width="20%" align="center"><a href="README.md">Background</a></td>
    <td width="20%" align="center"><a href="PREREQUISITES.md">Prerequisites</a></td> 
    <td width="20%" align="center"><b>Compile on AWS with Merlin</b></td> 
    <td width="20%" align="center"><a href="DEPLOY.md">Deploy on F1</a></td>
  </tr>
</table>

------------------------------------

**How to compile with Merlin for the AWS F1 target platform**<br>
In this tutorial, we will use a simple design “vector_add” to illustrate how to compile, with Merlin and run on AWS F1 instance. These steps can be applied to all the design examples.

**Get the Example code**<br>
On the Merin instance created in the previous section (please refer to the previous section: <a href="PREREQUISITES.md">Prerequisites</a>)
```
git clone https://github.com/falconcomputing/merlin-compiler.git
cd merlin-compiler/Examples/vectoradd
```

**View the available make commands**<br>
```
make 

**************************************************************************************
* Merlin Compiler Makefile                                                           *
* Copyright (C) 2015-2019 Falcon Computing Solutions, Inc. - All rights reserved.    *
*                                                                                    *
* Usage: make <hardware_target> <command>                                            *
* Available hardware targets:                                                        *
* cpu    : compile for cpu only                                                      *
* intel  : compile for intel FPGAs                                                   *
* xilinx : compile for xilinx FPGAs (includes AWS F1)                                *
* clean  : clean temp files                                                          *
*                                                                                    *
* Available commands:                                                                *
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
make cpu run
```

Notice how long the code took to finish execution on the CPU. Record the performance for future comparisons again the accelerated version.
***Compile the FPGA binary (bitstream)***
Generate the  .xclbin file
```
make xilinx mcc_bitgen
```

***Generate an AFI file and submit to AWS***<br>
Configure your AWS security credentials

```
aws configure
AWS Access Key ID [None]: <Enter your access-ID>
AWS Secret Access Key [None]: <Enter your secret key>
Default region name [None]: us-east-1
```

Run the command below to generate AFI from .xclbin file. A file with extension .awsxclbin will be generated after the compilation is completed.

The .xclbin files can be located under: 
* <example_folder>/build/xilinx_dse/
* <example_folder>/build/xilinx_mo/

```
export SDACCEL_DIR=/home/centos/aws-fpga/SDAccel
cd vectoradd/build/xilinx_mo 
$SDACCEL_DIR/tools/create_sdaccel_afi.sh -xclbin=vec_add_kernel_hw.xclbin -o=vec_add_kernel_hw -s3_bucket=fcs-fpga -s3_dcp_key=dcp -s3_logs_key=log
```

Similarly, you can follow same steps for the Xilinx DSE compile under vectoradd/build/xilinx_dse.

.awsxclbin file is a wrapper that has the information (AGFI ID) for the F1 runtime library to find the AFI to configure the F1 FPGA. Even though the .awsxclbin file is generated right away, the actual AFI generation can take up to an hour to complete. 
Check on the status of the submitted AFI to AWS.

Hint: If you see “ERROR: Directory to_aws already exists”, error simple delete the “to_aws” directory and rerun the command.

Run this command to find the FPGA Image ID:
```
cat *afi_id.txt
```
The output will look like this:
```
{
    "FpgaImageId": "afi-08b2ee4196d2a0922",
    "FpgaImageGlobalId": "agfi-08142f7ccb0131f3a"
}
```
Capture the "FpgaImageId": "afi-xxxxxxxxxxxxxxxxx"** from the output. 

Use this "afi-xxxxxxxxxxxxxxxxx" to run the command below to check the AFI status. 
```
aws ec2 describe-fpga-images --fpga-image-ids <FpgaImageId_from_previous_step>
```

The output says "Code": "Pending" initially. And it will eventually turn into ""Code": "available". Please note that step may take up to 1 hour.

```
        "FpgaImageGlobalId": "agfi-xxxxxxxxxxxxxxxxxxxx",
        "State": {
            "Code": "available"
        },
        "ShellVersion": "0x071417d3",
        "OwnerId": "xxxxxxxxxx",
        "FpgaImageId": "afi-xxxxxxxxxxxxxxxxx", 
        …
```
Once the AFI is available by AWS, the "State" "Code" will say "available" and you can move to the next step.  The final outcome of this step is a file with a .awsaxlbin extention on disk. You can verify it exists as well using this command.
```
ls -la vec_add_kernel_hw.awsxclbin
```

***Compile your host executable***
Next step is to generate the host binary and library files:
```
make mcc_accexe
```

***Package the files required to deploy on F1***
Copy host executable, .so  library, *.awsxclbin FPGA binary and any test data files you need from previous steps to the F1 instance.  
```
make mcc_pkg
```
At this point you should see a vectoadd_pkg.tar.gz file has been created.
```
ls -la vectoradd_pkg.tar.gz
```
This is the file you you need to transfer to AWS F1 instance for deployment in the next section.

***Please note this is xilinx_mo folder can you can repeat the same steps above for xilinx_dse compile folder.***
<br>
<br>
Start the next module: <a href="DEPLOY.md">Deploy on F1</a>
