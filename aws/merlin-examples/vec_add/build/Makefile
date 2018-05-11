# Copyright (C) 2015-2018 Falcon Computing Solutions, Inc. - All rights reserved.

# Choose target FPGA platform & vendor
VENDOR=XILINX
#DEVICE=xilinx:adm-pcie-ku3:2ddr:3.3
DEVICE=F1

# Edit Options per your setup if using AWS F1
#S3_OPT=-s3_bucket=<YOUR_BUCKET_NAME> -s3_dcp_key=dcp -s3_logs_key=log

# Host Code Compilation settings
HOST_SRC_FILES=../src/main.cpp ../src/vec_add.cpp

# Executable names and arguments
EXE=test
ACC_EXE=test_acc
EXE_ARGS=

CXX=g++
CXX_INC_DIRS=-I ../include -I ./ -I $(MACH_COMMON_DIR)
CXX_FLAGS+= $(CXX_INC_DIRS) -Wall -O3
#CXX_FLAGS+= -Wall
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

