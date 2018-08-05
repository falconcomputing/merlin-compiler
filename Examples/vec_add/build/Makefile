# Copyright (C) 2015-2018 Falcon Computing Solutions, Inc. - All rights reserved.

# Choose target FPGA platform & vendor
VENDOR=XILINX
DEVICE=xilinx_vcu1525_dynamic_5_0
#DEVICE=xilinx:aws-vu9p-f1:4ddr-xpr-2pr:4.0

#VENDOR=INTEL
#DEVICE=pac_a10
#DEVICE=a10gx

# Edit Options per your setup if using AWS F1
#S3_OPT=-s3_bucket=<YOUR_BUCKET_NAME> -s3_dcp_key=dcp -s3_logs_key=log

# Host Code Compilation settings
HOST_SRC_FILES=../src/main.cpp 

# Executable names and arguments
EXE=test
ACC_EXE=test_acc
EXE_ARGS=

CXX=g++
CXX_INC_DIRS=-I ../include -I ./ -I $(MACH_COMMON_DIR)
CXX_FLAGS+= $(CXX_INC_DIRS) -Wall -O3
ifeq ($(VENDOR),XILINX)
CXX_FLAGS +=-lstdc++ -L$(XILINX_SDX)/lib/lnx64.o
endif

# Accelerated Kernel settings
KERNEL_NAME=vec_add_kernel
KERNEL_SRC_FILES=../src/vec_add_kernel.cpp
KERNEL_INC_DIR=$(CXX_INC_DIRS)
CMP_OPT=
LNK_OPT=

MCC_COMMON_DIR=../../common
include $(MCC_COMMON_DIR)/mcc_common.mk

