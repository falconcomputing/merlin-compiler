# Copyright (C) 2019 Falcon Computing Solutions, Inc. - All rights reserved.
#
# Choose target FPGA platform & vendor
VENDOR=XILINX
PLATFORM=vitis::xilinx_u250_xdma_201830_1
#PLATFORM=vitis::xilinx_aws-vu9p-f1_shell-v04261818_201920_2

# Edit Options per your setup if using AWS F1
#S3_OPT=-s3_bucket=fcs-fpga -s3_dcp_key=dcp -s3_logs_key=log

# Host Code Compilation settings
SRC_DIR:=../src
INC_DIR:=
#COMMON_DIR:=../../common
HOST_SRC_FILES=$(SRC_DIR)/main.cpp
DATA_DIR=
F1_DATA_DIR=

# Executable names and arguments
EXE=dot
ACC_EXE=$(EXE)_acc

# Testing mode
EXE_ARGS= 
F1_EXE_ARGS= 

CXX_INC_DIRS=-I. -I$(INC_DIR)
CXX_FLAGS+= $(CXX_INC_DIRS)
CXX_FLAGS+= -Wall -O3 -lrt
#CXX_FLAGS+= -g

# Accelerated Kernel settings
KERNEL_NAME=dot_product
KERNEL_SRC_FILES=$(SRC_DIR)/dot_product.cpp
KERNEL_INC_DIR=$(CXX_INC_DIRS)

# MerlinCC Options
#AUTODSE=1
CMP_OPT=-funsafe-math-optimizations
LNK_OPT=

#common make
MCC_COMMON_DIR=../../common
include $(MCC_COMMON_DIR)/mcc_common.mk
