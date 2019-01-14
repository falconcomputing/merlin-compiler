
<table style="width:100%">
  <tr>
    <th width="100%" colspan="6"><h2>Merlin on AWS</h2></th>
  </tr>
  <tr>
    <td width="20%" align="center"><a href="README.md">Background</a></td>
    <td width="20%" align="center"><b>Prerequisites</b></td> 
    <td width="20%" align="center"><a href="COMPILE.md">Compile on AWS with Merlin</a></td> 
    <td width="20%" align="center"><a href="DEPLOY.md">Deploy on F11</a></td>
  </tr>
</table>

------------------------------------
**Prerequisites**<br>
This section is a step by step guide on how to acquire these resources to be able to compile and accelerate your application on AWS using Merlin.

* An AWS account
* Merlin AMI Instance
* Merlin License
* F1 Instance
* S3 Bucket

***AWS Account***<br>
<a href="https://aws.amazon.com/free/">Setup an AWS Account</a>

***Setting up a Merlin AMI, EC2 Instances to Compile***<br>
To compile with Merlin on AWS, you need to create EC2 instance that includes both Merlin Compiler and SDAccel. This can be achieved via the Merlin AMI and following these steps:
* Contact support@falcon-computing.com for AMI ID and License
* Launch your browser and login to EC2 Management Console
* Click IMAGES->AMIs on the left side of the page
* Search for the AMI ID provided by Falcon suppot. This AMI includes Merlin Compiler and SDAccel setup.
* Click Launch on the left side of the page
* **C4.2XLarge** is recommended to compile your aplication with Merlin
* On step 3 till step7, just use default settings and click Review and Launch
* On step 7, click Launch and you will select an existing key pair or create a new key pair, please choose one accordingly and launch the instance
* After you create one instance successfully, login to this instance, replace INSTANCE_IP with the actual IP
```
ssh -i ~/.ssh/user.pem centos@<INSTANCE_IP>
```

Account configuration:
•	`~/.aws/{config,credentials}` have to be created by the user through 'aws configure'

***Obtaining and setting up Merlin License***<br>
A valid Merlin license needs to be setup in the environment variable $FALCONLM_LICENSE_PATH. If the license file is improperly configured, an error message will be reported. And this is a BYOL (Bring Your Own License) product.  

To obtain an evaluation license, please email support@falcon-computing.com. 

When you recieve your license, setup this environemnt variable at the Merlin Instance created in the previous step.

```
export FALCONLM_LICENSE_FILE=/path/to/license.lic
```
Please make sure the Xilinx SDK license is available in the environment variable $XILINXD_LICENSE_FILE.
```
export XILINXD_LICENSE_FILE=/path/to/license.lic
```

Alternatively, you can add these to the .bashrc script. So it automatically executes everytime you login to the instance via ssh. Therefore, you don't need to type them everytime you login to the Merlin instance.
```
vi ~/.bashrc
```
Add these lines:
```
export FALCONLM_LICENSE_FILE=/path/to/license.lic
export XILINXD_LICENSE_FILE=/path/to/license.lic
```
Save the file

***Setting up F1, EC2 Instances to Run Application on FPGA***<br>
After compiling the application using Merlin instance, you will need to launch an AWS F1 instance to run the accelerated application FPGA. using the "FPGA Developer AMI" which comes pre-installed with SDAccel and required licenses.  We recommend **f1.2xlarge** for this step. More detailed instructions can be found 
<a href="https://github.com/Xilinx/SDAccel_Examples/wiki/Create,-configure-and-test-an-AWS-F1-instance">here</a>.

***Create a S3 bucket with the name “fcs-fpga"***

-	Launch your browser and login to AWS
-	Click on Services menu; now click on S3 link under Storage category
-	In the S3 buckets page, click on “Create bucket” button
-	Enter “fcs-fpga” as the Bucket name; enter the same region name as the C4.2X large instance from the step above
-	Select defaults for rest of the parameters
<br>
<br>
Start the next module: <a href="COMPILE.md">Compile on AWS with Merlin</a>

