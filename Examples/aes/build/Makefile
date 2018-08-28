# Choose target FPGA platform vendor
VENDOR=XILINX
DEVICE=xilinx_vcu1525_dynamic_5_0
#VENDOR=INTEL
#DEVICE=a10gx

# Host Code Compilation settings
HOST_COMMON_DIR=../../common/host
HOST_SRC_FILES=$(HOST_COMMON_DIR)/harness.cpp ../src/local_support.cpp $(HOST_COMMON_DIR)/support.cpp

# Executable names and arguments
EXE=test_aes
ACC_EXE=test_accaes
EXE_ARGS=../data/input.data ../data/check.data

CXX=g++
CXX_INC_DIRS=-I ../src -I ../include -I ./ -I $(HOST_COMMON_DIR)
CXX_FLAGS+= $(CXX_INC_DIRS) -Wall -O3
#CXX_FLAGS+= -Wall
#CXX_FLAGS+= -g
ifeq ($(VENDOR),XILINX)

CXX_FLAGS +=-lstdc++ -L$(XILINX_SDX)/lib/lnx64.o
endif

# Accelerated Kernel settings
KERNEL_NAME=aes256_encrypt_ecb_kernel
KERNEL_SRC_FILES=../src/aes.cpp
KERNEL_INC_DIR=$(CXX_INC_DIRS)
CMP_OPT=
LNK_OPT=

MCC_COMMON_DIR=../../common
include $(MCC_COMMON_DIR)/mcc_common.mk
