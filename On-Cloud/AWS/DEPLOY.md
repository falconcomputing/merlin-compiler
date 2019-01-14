<table style="width:100%">
  <tr>
    <th width="100%" colspan="6"><h2>Merlin on AWS</h2></th>
  </tr>
  <tr>
    <td width="20%" align="center"><a href="README.md">Background</a></td>
    <td width="20%" align="center"><a href="PREREQUISITES.md">Prerequisites</a></td> 
    <td width="20%" align="center"><a href="COMPILE.md">Compile on AWS with Merlin</a></td> 
    <td width="20%" align="center"><b>Deploy on F1</b></td>
  </tr>
</table>

------------------------------------
***Creating AWS F1 Instance***<br>
You will need F1 instance for the following steps to deploy and run your accelerated application using FPGAs. For instructions, how to create F1, please refer to "Setting up F1, EC2 Instances to Run Application on FPGA" in the <a href="PREREQUISITES.md">Prerequisites</a> section. 

***Running Your Accelerated Application on AWS F1***<br>
1. Copy the package 
Use scp to copy the package files that contains all the necessary files from the compile host to the F1 instance:
```
scp -i ~/user.pem vectoradd_pkg.tar.gz centos@<f1_instance_ip_address>:~/
```
2. Login to  F1

```
ssh -i ~/user.pem centos@<f1_instance_ip_address>
```
3. Unpack the files on F1
```
tar xvzf vectoradd_pkg.tar.gz
```

4. Setup F1 (if you haven't done that before)
```
git clone https://github.com/aws/aws-fpga.git $AWS_FPGA_REPO_DIR
pushd .
cd $AWS_FPGA_REPO_DIR 
source sdaccel_setup.sh
popd
```
Source the Runtime Environment & Execute your Host Application


For Xilinx SDx 2018.2:
```
    sudo sh
    source /opt/xilinx/xrt/setup.sh   # Other runtime env settings needed by the host app should be setup after this step

```
5. Run the application 
```
cd ~centos/vectoradd_pkg
make mcc_runhw
```
4. Record how long the code took to finish execution using the FPGA.
5. Compare to the timing you recorded eariler using the CPU only execution to asess the F1 speed-ups vs. CPU.

You can find more C/C++ Merlin Examples <a href="../../Examples/README.md">here </a>
