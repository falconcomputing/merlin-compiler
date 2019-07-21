## Merlin Compiler on-premise

### Merlin Compiler Installation and Configuration
#### 1. System Requirements
* Linux 64-bit with at least 32GB of RAM with Docker CE version 1.13.1 or higher installed. For instructions on installing Docker please refer to https://docs.docker.com/install/.
* To use Merlin Compiler with Xilinx FPGA development boards, Xilinx SDAccel Development Environment v2018.3 or v2019.1 is required. Please follow instructions in SDx Environments Release Notes, Installation, and Licensing Guide to obtain a license and install the software and its supported FPGA platforms
* To use Merlin Compiler with Intel FPGA development boards, Intel FPGA SDK for OpenCL v18.1 or v19.1 is required. Please follow instructions in Intel FPGA SDK for OpenCL Getting Started Guide to obtain a license and install the software and its supported FPGA platforms.

#### 2. Installing and Configuring Merlin Compiler
  Merlin Compiler is packaged as a tar gzip file. 
* Download the tar gzip file from the link provided by the Falcon support team
* Extract and install the tool using the following command  
  $ tar xzvf <merlin_package>.tgz  
  A directory named “merlin” is created after extraction
* Follow the instructions in “merlin/README.md” to install and set up Merlin  
  Follow vendor tool installing instructions to install and configure vendor tools if they are not done yet. A single Merlin Compiler installation can be configured to support both Intel FPGA SDK for OpenCL and Xilinx SDAccel Environment.

#### 3. Obtaining and Installing Merlin Compiler License 
  Merlin Compiler license is for Merlin Compiler only. Users need to obtain separate licenses from Intel and/or Xilinx for Merlin Compiler to work with Intel FPGA for OpenCL and Xilinx SDAccel Environments, respectively.

   **Obtaining Merlin Compiler License**  
   Merlin Compiler supports floating licenses. Please send the MAC address of your license server to support@falcon-computing.com to order and retrieve the license file. Below is an example using ifconfig command to get the MAC address: 01:23:45:67:89:AB  
    $ ifconfig -a  
    eth0      Link encap:Ethernet  HWaddr 01:23:45:67:89:AB  
              BROADCAST MULTICAST  MTU:1500  Metric:1  
              RX packets:0 errors:0 dropped:0 overruns:0 frame:0  
              TX packets:0 errors:0 dropped:0 overruns:0 carrier:0  

   **Installing Floating License**
* Open the license file and replace the highlighted words as instructed below:  
   SERVER **hostname** host_id **port**  
   VENDOR falconlm **merlin_root**/license/falconlm  

   **hostname**:  license server hostname as returned by Linux hostname command  
   **port**: network port number for the license  
   **merlin_root**:  the path of the directory ‘merlin’ in your Merlin installation  
* Run the command below to starting the license server  
  $ **merlin_root**/license/lmgrd -c license.lic -l lmgrd.log  
  Check lmgrd.log file for the status and additional messages of the license server
* Set the environment variable below to enable Merlin Compiler license  
  $export LM_LICENSE_FILE=**port**@**hostname**  
  Use the same **port** and **hostname** specified in the updated license file. If you already have the environment variable defined, just append Merlin license to the variable.

