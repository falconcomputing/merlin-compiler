<table style="width:100%">
  <tr>
    <th width="100%" colspan="6"><h2>Merlin Compiler</h2></th>
  </tr>
  <tr>
    <td width="20%" align="center"><a href="README.md">1. Introduction</a></td>
    <td width="20%" align="center"><a href="DEVELOPING_FOR_FPGA.md">2. Developing for FPGAs</a></td> 
    <td width="20%" align="center"><b>3. Working with Merlin</b></td>
    <td width="20%" align="center"><a href="PLATFORM_SPECIFIC.md">4. Platform-Specific</a></td>
   </tr>
</table>

---------------------------------------
**3. Working with Merlin**<br>
Merlin compiler offers OpenMP-like pragma interface. As mentioned in the previous section, the user can either leverage the Deep Space Exploration flow (DSE), or the Manually Optimized (MO) flow.

In order to understand both modes of operations, let's take a look at this scenario. This is a snippet from the BlackScholes Asian Option pricing financial algorithm. First we show the CPU version, without any Merlin pragmas.

```
//blackAsian.cpp
void blackAsian(data_t call[1], data_t put[1],   // call price and put price
                data_t timeT,                    // time period of options
                data_t freeRate,                 // interest rate of the riskless asset
                data_t volatility,               // volatility of the risky asset
                data_t initPrice,                // stock price at time 0
                data_t strikePrice)              // strike price
{

        stockData sd(timeT,freeRate,volatility,initPrice,strikePrice);
        blackScholes bs(sd);
        data_t callPrice,putPrice;
        bs.simulation(&callPrice,&putPrice);
        *call=callPrice;
        *put=putPrice;
}
```
```
//blackScholes.cpp
void blackScholes::sampleSIM(RNG* mt_rng, data_t *pCall, data_t *pPut)
{
        const data_t Dt=data.timeT/data_t(NUM_STEPS);
        const data_t ratio1=expf(-data.freeRate*data.timeT);
        const data_t ratio2=(data.freeRate-data.volatility*data.volatility*0.5f)*Dt;
        const data_t ratio3=Dt*data.volatility*data.volatility;
        const data_t initValue=logf(data.initPrice/NUM_STEPS/1.0f);
        data_t call=0.0f,put=0.0f;
        data_t sum_call[NUM_RNGS], sum_put[NUM_RNGS];
        data_t sum_call1[NUM_RNGS], sum_put1[NUM_RNGS];
        data_t acc1[NUM_RNGS][NUM_SIMS],acc[NUM_RNGS][NUM_SIMS];
        data_t ave1[NUM_RNGS][NUM_SIMS],ave[NUM_RNGS][NUM_SIMS];
        data_t num1[NUM_RNGS][NUM_SIMS],num2[NUM_RNGS][NUM_SIMS];

        for(int k=0;k<NUM_SIMS;k++) {
                for(int i=0;i<NUM_RNGS;i++) {
                        if(k==0) {
                                sum_call[i]=0.0f;
                                sum_put[i]=0.0f;
                                sum_call1[i]=0.0f;
                                sum_put1[i]=0.0f;
                        }
                        acc1[i][k]=initValue;
                        ave1[i][k]=-data.strikePrice;
                        acc[i][k]=initValue;
                        ave[i][k]=-data.strikePrice;
                }
        }
        for(int s=0;s<NUM_SIMGROUPS;s+=2) {
                for(int p=0;p<NUM_STEPS;p++) {
                        for(int k=0;k<NUM_SIMS;k++) {
                                for(int i=0;i<NUM_RNGS;i++) {
                                        mt_rng[i].BOX_MULLER(&num1[i][k],&num2[i][k],ratio3);
                                        acc1[i][k]+=ratio2+num1[i][k];
                                        ave1[i][k]+=expf(acc1[i][k]);
                                        acc[i][k]+=ratio2+num2[i][k];
                                        ave[i][k]+=expf(acc[i][k]);
                                }
                        }
                }
                for(int k=0;k<NUM_SIMS;k++) {
                        for(int i=0;i<NUM_RNGS;i++) {
                                if(ave[i][k]>0.0f)
                                        sum_call[i]+=ave[i][k];
                                else
                                        sum_put[i]+=ave[i][k];
                                if(ave1[i][k]>0.0f)
                                        sum_call1[i]+=ave1[i][k];
                                else
                                        sum_put1[i]+=ave1[i][k];
                                acc1[i][k]=initValue;
                                ave1[i][k]=-data.strikePrice;
                                acc[i][k]=initValue;
                                ave[i][k]=-data.strikePrice;
                        }
                }
        }
                           
        for(uint i=0;i<NUM_RNGS;i++) {
                call+=sum_call[i]+sum_call1[i];
                put+=sum_put[i]+sum_put1[i];
        }
        *pCall=ratio1*call/(NUM_SIMS*NUM_RNGS*NUM_SIMGROUPS*1.0f);
        *pPut =-ratio1*put/(NUM_SIMS*NUM_RNGS*NUM_SIMGROUPS*1.0f);
}

void blackScholes::simulation(data_t *call, data_t *put)
{
        RNG mt_rng[NUM_RNGS];
        uint seeds[NUM_RNGS];

        for(int i=0;i<NUM_RNGS;i++) {
                seeds[i]=i;
        }
        RNG::init_array(mt_rng,seeds,NUM_RNGS);
        sampleSIM(mt_rng,call,put);
}
```

As we can see the function is calling another sub-function. Taking advantage of the DSE mode of operation (enabled by passing -auto_dse=on to merlincc command line), the function required be accelerated, by inserting a single pragma: **#pragma ACCEL kernel**. This pragma indicates the begining of the kernel function as illustrated in the code snippet below.

```
//blackAsian.cpp

#pragma ACCEL kernel
void blackAsian(data_t call[1], data_t put[1],   // call price and put price
                data_t timeT,                           // time period of options
                data_t freeRate,                        // interest rate of the riskless asset
                data_t volatility,                      // volatility of the risky asset
                data_t initPrice,                       // stock price at time 0
                data_t strikePrice)                     // strike price
{

        stockData sd(timeT,freeRate,volatility,initPrice,strikePrice);
        blackScholes bs(sd);
        data_t callPrice,putPrice;
        bs.simulation(&callPrice,&putPrice);
        *call=callPrice;
        *put=putPrice;
}

```
In the MO mode of operation, the user may need to add further pragmas to the sub-funcions and inner loops. Here're examples of such pragmas: **#pragma ACCEL parallel**. This is also illustrated further in the code snippet below.

```
void blackScholes::sampleSIM(RNG* mt_rng, data_t *pCall, data_t *pPut)
{
        const data_t Dt=data.timeT/data_t(NUM_STEPS);
        const data_t ratio1=expf(-data.freeRate*data.timeT);
        const data_t ratio2=(data.freeRate-data.volatility*data.volatility*0.5f)*Dt;
        const data_t ratio3=Dt*data.volatility*data.volatility;
        const data_t initValue=logf(data.initPrice/NUM_STEPS/1.0f);
        data_t call=0.0f,put=0.0f;
        data_t sum_call[NUM_RNGS], sum_put[NUM_RNGS];
        data_t sum_call1[NUM_RNGS], sum_put1[NUM_RNGS];
        data_t acc1[NUM_RNGS][NUM_SIMS],acc[NUM_RNGS][NUM_SIMS];
        data_t ave1[NUM_RNGS][NUM_SIMS],ave[NUM_RNGS][NUM_SIMS];
        data_t num1[NUM_RNGS][NUM_SIMS],num2[NUM_RNGS][NUM_SIMS];

        for(int k=0;k<NUM_SIMS;k++) {
#pragma ACCEL parallel
                for(int i=0;i<NUM_RNGS;i++) {
                        if(k==0) {
                                sum_call[i]=0.0f;
                                sum_put[i]=0.0f;
                                sum_call1[i]=0.0f;
                                sum_put1[i]=0.0f;
                        }
                        acc1[i][k]=initValue;
                        ave1[i][k]=-data.strikePrice;
                        acc[i][k]=initValue;
                        ave[i][k]=-data.strikePrice;
                }
        }
        for(int s=0;s<NUM_SIMGROUPS;s+=2) {
                for(int p=0;p<NUM_STEPS;p++) {
                        for(int k=0;k<NUM_SIMS;k++) {
#pragma ACCEL parallel
                                for(int i=0;i<NUM_RNGS;i++) {
                                        mt_rng[i].BOX_MULLER(&num1[i][k],&num2[i][k],ratio3);
                                        acc1[i][k]+=ratio2+num1[i][k];
                                        ave1[i][k]+=expf(acc1[i][k]);
                                        acc[i][k]+=ratio2+num2[i][k];
                                        ave[i][k]+=expf(acc[i][k]);
                                }
                        }
                }
                
                for(int k=0;k<NUM_SIMS;k++) {
#pragma ACCEL parallel
                        for(int i=0;i<NUM_RNGS;i++) {
                                if(ave[i][k]>0.0f)
                                        sum_call[i]+=ave[i][k];
                                else
                                        sum_put[i]+=ave[i][k];
                                if(ave1[i][k]>0.0f)
                                        sum_call1[i]+=ave1[i][k];
                                else
                                        sum_put1[i]+=ave1[i][k];
                                acc1[i][k]=initValue;
                                ave1[i][k]=-data.strikePrice;
                                acc[i][k]=initValue;
                                ave[i][k]=-data.strikePrice;
                        }
                }
        }
                                                                                                
        for(uint i=0;i<NUM_RNGS;i++) {
                call+=sum_call[i]+sum_call1[i];
                put+=sum_put[i]+sum_put1[i];
        }
        *pCall=ratio1*call/(NUM_SIMS*NUM_RNGS*NUM_SIMGROUPS*1.0f);
        *pPut =-ratio1*put/(NUM_SIMS*NUM_RNGS*NUM_SIMGROUPS*1.0f);
}

void blackScholes::simulation(data_t *call, data_t *put)
{
        RNG mt_rng[NUM_RNGS];
        uint seeds[NUM_RNGS];

#pragma ACCEL parallel
        for(int i=0;i<NUM_RNGS;i++)        {
                seeds[i]=i;
        }
        RNG::init_array(mt_rng,seeds,NUM_RNGS);
        sampleSIM(mt_rng,call,put);
}
```

<br>
<br>
Start the next module: <a href="PLATFORM_SPECIFIC.md">4. Platform-Specific</a>
