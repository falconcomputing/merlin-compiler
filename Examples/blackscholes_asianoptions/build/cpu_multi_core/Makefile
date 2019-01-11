# Copyright (C) 2019 Falcon Computing Solutions, Inc. - All rights reserved.
#
# Choose target FPGA platform & vendor
VENDOR=CPU

# Edit Options per your setup if using AWS F1

# Host Code Compilation settings
SRC_DIR:=../../src
#COMMON_DIR:=../../common
INC_DIR:=../../include
HOST_SRC_FILES=$(SRC_DIR)/main.cpp
DATA_DIR=../../data

# Executable names and arguments
EXE=blackasian
ACC_EXE=blackasian_acc
# Testing mode
EXE_ARGS= -f $(DATA_DIR)/blackAsian.parameters

CXX_INC_DIRS=-I ./ -I $(INC_DIR) 
CXX_FLAGS+= $(CXX_INC_DIRS)
CXX_FLAGS+= -Wall -O3 -lrt
CXX_FLAGS+=-DPLATFORM=\"$(PLATFORM)\" -DKERNEL=\"$(KERNEL_NAME)\" -DKERNEL_NAME=$(KERNEL_NAME) -DBLACKASIAN=1
# Uncomment the following line to compile the Baseline
CXX_FLAGS+= -DBASELINE=1 -fopenmp
#CXX_FLAGS+= -g

# Accelerated Kernel settings
KERNEL_NAME=blackAsian

KERNEL_SRC_FILES=$(SRC_DIR)/blackAsian.cpp $(SRC_DIR)/stockData.cpp $(SRC_DIR)/blackScholes_omp.cpp $(SRC_DIR)/RNG.cpp 
KERNEL_INC_DIR=$(CXX_INC_DIRS)

# MerlinCC Options
# Uncomment the following lines to compile with Baseline
CMP_OPT+= -DBASELINE=1
LNK_OPT+= -DBASELINE=1

#common make
MCC_COMMON_DIR=../../../common
include $(MCC_COMMON_DIR)/mcc_common.mk

