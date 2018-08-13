## Falcon image for Merlin Compiler on AWS

### License:

Falcon License: A valid license needs to be setup in the environment variable $FALCONLM_LICENSE_PATH. If the license file is improperly configured, an error message will be reported. And this is a BYOL (Bring Your Own License) product. Please email support@falcon-computing.com to acquire the license.

FALCONLM_LICENSE_FILE=/path/to/license.lic or port@server

Also please make sure the Xilinx SDK license is available in the environment variable $XILINXD_LICENSE_FILE.

XILINXD_LICENSE_FILE=/path/to/license.lic or port@server
 ```
Steps to create EC2 instance to include Merlin Compiler and SDAccel:
1. open a web browser and login to EC2 Management Console
2. Click IMAGES->AMIs on the left side of the page
3. Get the AMI ID (ami-0622a96fe197c8bd3) or AMI Name (merlin-compiler-2.2.1) which includes Merlin Compiler and SDAccel (2017.4) setup
4. Click Launch on the left side of the page
5. on step 2 for instance type please choose General purpose (m4.2xlarge) and click Next
6. on step 3 till step7, just use default settings and click Review and Launch
7. on step 7, click Launch and you will select an existing key pair or create a new key pair, please choose one accordingly and launch instance

After you create one instance successfully, login to this instance, replace INSTANCE_IP with the actual IP
ssh -i ~/.ssh/user.pem centos@<INSTANCE_IP>

Account configuration:
`~/.aws/{config,credentials}` have to be created by the user through 'aws configure'
 ```
 
### Example
 ```
$cd /home/centos/Examples/vec_add/build/
$make
**** Merlin Compiler Makefile
**** Copyright (C) 2015-2018 Falcon Computing Solutions, Inc. - All rights reserved.

$ make <target>
Available targets:
           run - Compile and Run TB Executable on CPU (without Acceleration)
       mcc_acc - Use Merlin Compiler to compile the Acceleration Kernel code
    mcc_runsim - Generate kernel binary for simulation on CPU and run it
  mcc_estimate - Get resource and performance estimates
    mcc_bitgen - Generate kernel binary for Acceleration Platform
    mcc_afigen - Generate AFI for AWS F1 FPGA
     mcc_runhw - Run TB Executable on Host CPU and accelerated kernel on platform HW
         clean - Remove all output products (except for bitgen outputs)
$make mcc_afigen

Or

$make mcc_bitgen
Run the command below to generate AFI from .xclbin file. Replace mykernel with the actual kernel name.
$/home/aws-fpga/SDAccel/tools/create_sdaccel_afi.sh -xclbin=mykernel.xclbin \
      -o=mykernel -s3_bucket=fcs-fpga -s3_dcp_key=dcp -s3_logs_key=log

A file with extension .awsxclbin will be generated after the compilation is completed.

.awsxclbin file is a wrapper that has the information (AGFI ID) for the F1 runtime library to find the AFI to configure the F1 FPGA. Even though the .awsxclbin file is generated right away, the actual AFI generation can take up to an hour to complete. Run the command below to check the AFI status. Once the AFI is available, you can run the test on AWS F1 FPGA.
 ```
 
$aws ec2 describe-fpga-images

            …
            "FpgaImageGlobalId": "agfi-xxxxxxxxxxxxxxxxxxxx",
            "State": {
                "Code": "available"
            },
            "ShellVersion": "0x071417d3",
            "OwnerId": "xxxxxxxxxx",
            "FpgaImageId": "afi-xxxxxxxxxxxxxxxxx", 
            …

If AFI is available, you also need to generate the host binary and libary file (3 files: <kernel>_acc, *.so, *.awsxclbin will run AWS F1 FPGA).
