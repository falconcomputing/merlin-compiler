# Copyright (C) 2017 Falcon Computing Solutions, Inc. - All rights reserved.
#
# Choose target FPGA platform & vendor
VENDOR=XILINX
DEVICE=xilinx_aws-vu9p-f1-04261818_dynamic_5_0

# Edit Options per your setup if using AWS F1
#S3_OPT=-s3_bucket=fcs-fpga -s3_dcp_key=dcp -s3_logs_key=log

# Host Code Compilation settings
SRC_DIR:=../../src
INC_DIR:=../../include
COMMON_DIR:=../../common
HOST_SRC_FILES=$(SRC_DIR)/main.cpp
DATA_DIR=../../data
F1_DATA_DIR=./data


# Executable names and arguments
EXE=blackasian
ACC_EXE=$(EXE)_acc

# Testing mode
EXE_ARGS= -f $(DATA_DIR)/blackAsian.parameters
F1_EXE_ARGS= -f $(F1_DATA_DIR)/blackAsian.parameters


CXX_INC_DIRS=-I . -I $(INC_DIR)
CXX_FLAGS+= $(CXX_INC_DIRS)
CXX_FLAGS+= -Wall -O3 -lrt
CXX_FLAGS+=-DPLATFORM=\"$(PLATFORM)\" -DKERNEL=\"$(KERNEL_NAME)\" -DKERNEL_NAME=$(KERNEL_NAME) -DBLACKASIAN=1
#CXX_FLAGS+= -g

# Accelerated Kernel settings
KERNEL_NAME=blackAsian
KERNEL_SRC_FILES=$(SRC_DIR)/blackAsian.cpp $(SRC_DIR)/stockData.cpp $(SRC_DIR)/blackScholes.cpp $(SRC_DIR)/RNG.cpp
KERNEL_INC_DIR=$(CXX_INC_DIRS)

# MerlinCC Options
CMP_OPT= --attribute auto_func_inline=aggressive
LNK_OPT= 

#common make
MCC_COMMON_DIR=../../../common
include $(MCC_COMMON_DIR)/mcc_common.mk

