## Merlin Compiler on-premise

### Merlin Compiler Installation and Configuration
#### 1. System Requirements
    •   CentOS/RedHat 6.9 (or higher) 64-bit with at least 32GB of RAM
    •   To use Merlin Compiler with Intel FPGA development boards, Intel FPGA SDK for OpenCL v17.0.2 or v17,1.1 is required. Please follow instructions in Intel FPGA SDK for OpenCL Getting Started Guide to obtain a license and install the software and its supported FPGA platforms.
    •   To use Merlin Compiler with Xilinx FPGA development boards, Xilinx SDAccel Development Environment v2017.1 or v2017.4 is required. Please follow instructions in SDx Environments Release Notes, Installation, and Licensing Guide to obtain a license and install the software and its supported FPGA platforms
    •   gcc version must be 4.6.3 or higher
    •   Python 2.7
    •   The packages below need to be installed:
        $sudo yum install -y perl-XML-Simple python

#### 2. Downloading and Unpacking Merlin Compiler Package
    Merlin Compiler is packaged as a tar gzip file Merlin_Compiler_xxxx.tar.gz where xxxx is the date and version number.  
    •   Download the tar gzip file from the link provided by the Falcon support team
    •   Extract and install the tool using the following command:
        $tar xzvf Merlin_Compiler_xxxx.tar.gz
    •   A directory named “Merlin_Compiler_xxxx” is created. This user guide uses MERLIN_COMPILER_HOME environment variable to refer to the full pathname of this directory for illustration purpose.

#### 3. Configuring Merlin Compiler Installation
Merlin supports both C and Bash command shells. Bash shell commands are used in this user guide for illustration purpose.
NOTE: 
+ A single Merlin Compiler installation can be configured to support both Intel FPGA SDK for OpenCL and Xilinx SDAccel Environment
+ This step can be skipped if you have verified installations of vendors OpenCL SDK by following their software and board installation instructions
##### 3.1 Set up environments for FPGA vendors OpenCL SDK
    In general, follow vendor tool setup instructions to set up vendor tools. Just to make sure Merlin can find and invoke vendor tools.

    Run the commands below to set up Intel FPGA SDK for OpenCL 17.0.2
    $export ALTERA_QUARTUS_HOME=/path/to/Altera/17.0.2_pro
    $export ALTERAOCLSDKROOT=/path/to/Altera/17.0.2_pro/hld
    $export AOCL_BOARD_PACKAGE_ROOT=/path/to/Altera/17.0.2_pro/hld/board/a10_ref
    
    NOTE: Intel Arria 10 GX Development Kit is used as an example. Update ALTERAOCLSDKROOT and AOCL_BOARD_PACKAGE_ROOT to match the actual tool version and target board.
    
    Run the command below to set up environments for Xilinx SDAccel 2017.1
    $source /path/to/Xilinx/SDx/2017.1/settings64.sh
    
##### 3.2 Run the command below to set up the environment for running the Merlin Compiler
    $export PATH=$MERLIN_COMPILER_HOME/bin:$PATH

#### 4. Obtaining and Installing Merlin Compiler License 
    NOTE: Merlin Compiler license is for Merlin Compiler only. Users need to obtain separate licenses from Intel and Xilinx for Merlin Compiler to work with Intel FPGA for OpenCL and Xilinx SDAccel Environments, respectively.  

    Obtaining Merlin Compiler License
    Merlin Compiler supports node-locked and floating licenses. Please send the MAC address of your license server to support@falcon-computing.com to order and retrieve the license file. Below is an example using ifconfig command to get the MAC address: 01:23:45:67:89:AB
    $ifconfig -a
    eth0      Link encap:Ethernet  HWaddr 01:23:45:67:89:AB
              BROADCAST MULTICAST  MTU:1500  Metric:1
              RX packets:0 errors:0 dropped:0 overruns:0 frame:0
              TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
    
    Installing Floating License
    •   Open the license file and replace the highlighted words as instructed below:
    SERVER HOSTNAME HOST_ID PORT
    VENDOR falconlm $MERLIN_COMPILER_HOME/bin/falconlm
    
    HOSTNAME:  license server hostname as returned by Linux hostname command
    HOST_ID:  license server MAC address
    PORT: network port number for the license
    MERLIN_COMPILER_HOME: absolute path to Merlin Compiler installation directory
    
    •   Run the command below to starting the license server (floating license only)
    $$MERLIN_COMPILER_HOME/bin/lmgrd -c license.lic -l lmgrd.log
    Check lmgrd.log file for the status and additional messages of the license server
    
    •   Each user need to set the environment variable below to check out Merlin Compiler license
    $export FALCONLM_LICENSE_FILE=PORT@HOSTNAME
    Use the same PORT and HOSTNAME specified in the updated license file.
    
    Installing Node-locked License
    •   Save the node-locked license file on the server
    •   Each user need to set the environment variable below to use Merlin Compiler license
        $export FALCONLM_LICENSE_FILE=/path/to/license.lic

#### 5. Troubleshooting Merlin Compiler Installation
    •   “Can't locate XML/Simple.pm in @INC” is prompted when running Merling Compiler
    Solution: Please install Perl XML package with the following command:
    $sudo yum install -y perl-XML-Simple

