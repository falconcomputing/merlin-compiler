default: 
	@echo "**************************************************************************************"
	@echo "* Merlin Compiler Makefile                                                           *"
	@echo "* Copyright (C) 2015-2019 Falcon Computing Solutions, Inc. - All rights reserved.    *"
	@echo "*                                                                                    *"
	@echo "* Usage: make <hardware_target> <command>                                            *"
	@echo "* Available hardware targets:                                                        *"
	@echo "* cpu    : compile for cpu only                                                      *"
	@echo "* intel  : compile for intel FPGAs                                                   *"
	@echo "* xilinx : compile for xilinx FPGAs (includes AWS F1)                                *"
	@echo "* clean  : clean temp files                                                          *" 
	@echo "*                                                                                    *" 
	@echo "* Available commands:                                                                *"
	@echo "*          run - Compile and run executable on CPU without Acceleration (cpu only)   *"
	@echo "*   mcc_runsim - Generate kernel binary for simulation on CPU and run it             *"
	@echo "* mcc_estimate - Get resource and performance estimates                              *"
	@echo "*   mcc_bitgen - Generate kernel binary for Acceleration Platform                    *"
	@echo "*    mcc_runhw - Run executable on Host CPU and accelerated kernel on platform HW    *"
	@echo "*   mcc_afigen - Generate AFI for AWS F1 FPGA (AWS F1 users)                         *"
	@echo "*   mcc_accexe - compile accelerated executable on CPU and link with merlin runtime  *"
	@echo "*      mcc_pkg - Package all necessary files for running accelerated application     *"
	@echo "*        clean - Remove all output products (except for bitgen outputs)              *"
	@echo "**************************************************************************************"



cpu: 
	$(MAKE) -C build $(MAKECMDGOALS) 

intel: $(SUBDIRS)
	$(MAKE) -C build $(MAKECMDGOALS)  

xilinx: $(SUBDIRS)
	$(MAKE) -C build $(MAKECMDGOALS)  

clean: 
	$(MAKE) -C build clean  


run:

mcc_runsim:

mcc_estimate:

mcc_bitgen:

mcc_runhw:

mcc_afigen:

mcc_accexe:

mcc_pkg:

mcc_acc:


