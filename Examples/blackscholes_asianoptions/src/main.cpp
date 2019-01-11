/* 
======================================================
 Copyright 2016 Liang Ma

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
======================================================
*
* Author:   Liang Ma (liang-ma@polito.it)
*
* Host code defining all the parameters and launching the kernel. 
*
* Exception handling is enabled (CL_HPP_ENABLE_EXCEPTIONS) to make host code simpler.
*
* The global and local size are set to 1 since the kernel is written in C/C++ instead of OpenCL.
*
* Several input parameters for the simulation are defined in namespace Params
* and can be changed by using command line options. Only the kernel name must
* be defined.
*
* S0:		-s stock price at time 0
* K:		-k strike price
* rate:		-r interest rate
* volatility:	-v volatility of stock
* T:		-t time period of the option
*
*
* callR:	-c reference value for call price
* putR:		-p reference value for put price
* binary_name:  -a the .xclbin binary name
* kernel_name:  -n the kernel name
*----------------------------------------------------------------------------
*/

#define CL_HPP_ENABLE_EXCEPTIONS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "defTypes.h"
extern "C" 
void KERNEL_NAME(data_t *call, data_t *put, data_t timeT, data_t freeRate, data_t volatility, data_t initPrice, data_t strikePrice);

#ifdef USE_PROTOBUF
#include "bs.pb.h"
#include <google/protobuf/text_format.h>
#endif

#ifdef MCC_ACC
#ifdef MCC_SIM
#include "__merlinblackAsian_sim.h"
#else
#include "__merlinblackAsian.h"
#endif
#endif

using namespace std;

namespace Params 
{
	double initprice = 100;		    // -s
	double strikeprice = 110;			    // -k
	double rate = 0.05;   		// -r
	double volatility = 0.2;	// -v
	double time = 1.0;			    // -t
	const char *kernel_name=KERNEL;     // -n
	const char *binary_name=KERNEL ".hw." PLATFORM ".awsxclbin";     // -a
}
void usage(char* name)
{
    fprintf(stderr, "Usage: %s [-b binary_file_name] [-c call_price] [-p put_price] [-f param_file_name]\n", name);
}
int main(int argc, char** argv)
{
    int opt;
    double callR=-1, putR=-1;
    bool flagc=false,flagp=false;
    const char *param_filename=KERNEL ".parameters";
    while((opt=getopt(argc,argv,"b:c:p:f:"))!=-1){
	switch(opt){
	    case 'b':
		Params::binary_name=optarg;
		break;
	    case 'c':
		callR=atof(optarg);
		flagc=true;
		    break;
	    case 'p':
		putR=atof(optarg);
		flagp=true;
		break;
        case 'f':
        param_filename=optarg;
        break;
	    default:
		usage(argv[0]);
		return -1;
	}
    }

#ifdef MCC_ACC
    __merlin_init(argv[argc-1]);
#endif
#ifdef USE_PROTOBUF
    parameters::blackScholes params;
#endif
    FILE *is;
    is = fopen(param_filename, "rb");
    if(!is){
    fprintf(stderr, "Cannot open parameter file.\n");
	return -1;
    }
#ifdef USE_PROTOBUF
    const string str(istreambuf_iterator<char>(is), (istreambuf_iterator<char>()));
    google::protobuf::TextFormat::ParseFromString(str, &params);

    Params::time = params.time();
    Params::rate == params.rate();
    Params::volatility = params.volatility();
    Params::initprice = params.initprice();
    Params::strikeprice == params.strikeprice();
#else
    char line[1024];
    char param_val[1024];
    char tmp1[1024];
    char tmp2[1024];
    char tmp3[1024];
    char tmp4[1024];
    char tmp5[1024];
    char tmp6[1024];
    while (fgets(line, 1024, is)) {
        // clear tmp arrays
        memset(tmp1, 0, 1024);
        memset(tmp2, 0, 1024);
        memset(tmp3, 0, 1024);
        memset(tmp4, 0, 1024);
        memset(tmp5, 0, 1024);
        memset(tmp6, 0,  1024);

        memcpy(tmp1, line, strlen("initprice:"));
        memcpy(tmp2, line, strlen("strikeprice:"));
        memcpy(tmp3, line, strlen("rate:"));
        memcpy(tmp4, line, strlen("volatility:"));
        memcpy(tmp5, line, strlen("time:"));
        memcpy(tmp6, line, strlen("kernel_name:"));
        if (strcmp(tmp1, "initprice:") == 0) {
            memcpy(param_val, line + strlen("initprice:")+1, 1024 - strlen("initprice:")); 
            printf("initprice: %s\n", param_val);
            Params::initprice = atof(param_val);
        } else if (strcmp(tmp2, "strikeprice:") == 0) {
            memcpy(param_val, line + strlen("strikeprice:")+1, 1024 - strlen("strikeprice:")); 
            printf("strikeprice: %s\n", param_val);
            Params::strikeprice = atof(param_val);
        } else if (strcmp(tmp3, "rate:") == 0) {
            memcpy(param_val, line + strlen("rate:")+1, 1024 - strlen("rate:")); 
            printf("rate: %s\n", param_val);
            Params::rate = atof(param_val);
        } else if (strcmp(tmp4, "volatility:") == 0) {
            memcpy(param_val, line + strlen("volatility:")+1, 1024 - strlen("volatility:")); 
            printf("volatility: %s\n", param_val);
            Params::volatility = atof(param_val);
        } else if (strcmp(tmp5, "time:") == 0) {
            memcpy(param_val, line + strlen("time:")+1, 1024 - strlen("time:")); 
            printf("time: %s\n", param_val);
            Params::time = atof(param_val);
        } else if (strcmp(tmp6, "kernel_name:") == 0) {
            memcpy(param_val, line + strlen("kernel_name:")+1, 1024 - strlen("kernel_name:")); 
            printf("kernel_name: %s\n", param_val);
            Params::kernel_name = param_val;
        } else {
            fprintf(stderr, "Unknown parameter: %s\n", line);
        }
    }
#endif
    data_t h_call[1], h_put[1];
    printf("Starting execution. Time=%f rate=%f volatility=%f initprice=%f strikeprice=%f\n",
            Params::time,
            Params::rate,
            Params::volatility,
            Params::initprice,
            Params::strikeprice);
    printf("Starting blackAsian kernel.\n");

    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
#ifndef MCC_ACC
    blackAsian(h_call, h_put, Params::time, Params::rate, Params::volatility, Params::initprice, Params::strikeprice);
#else
    __merlin_blackAsian(h_call, h_put, Params::time, Params::rate, Params::volatility, Params::initprice, Params::strikeprice);
#endif
    clock_gettime(CLOCK_MONOTONIC, &finish);

    elapsed = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution completed.\n");
    printf("Execution time %f s\n", elapsed);
   
    printf("the call price is: %f\t", h_call[0]); 
    if(flagc) {
    printf("the difference with the reference value is %f%%", fabs(h_call[0]/callR-1)*100);
    }
    printf("\n");
    printf("the put price is %f\t", h_put[0]);
    if(flagp) {
    printf("the difference with the reference value is %f%%", fabs(h_put[0]/putR-1)*100);
    }
    printf("\n");

#ifdef MCC_ACC
    __merlin_release();
#endif
    return EXIT_SUCCESS;
}
