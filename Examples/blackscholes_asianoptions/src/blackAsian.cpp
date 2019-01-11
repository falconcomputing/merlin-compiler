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
* Top function is defined here with interface specified as axi4.
* It creates an object of blackScholes and launches the simulation.
*
*----------------------------------------------------------------------------
*/
#include "defTypes.h"
#include "stockData.h"
#include "blackScholes.h"

#if !defined(BASELINE) || defined(AUTODSE)
#pragma ACCEL kernel
#endif
extern "C"
void blackAsian(data_t call[1], data_t put[1],   // call price and put price
		data_t timeT,				// time period of options
		data_t freeRate,			// interest rate of the riskless asset
		data_t volatility,			// volatility of the risky asset
		data_t initPrice,			// stock price at time 0
		data_t strikePrice)			// strike price
{

	stockData sd(timeT,freeRate,volatility,initPrice,strikePrice);
	blackScholes bs(sd);
	data_t callPrice,putPrice;
	bs.simulation(&callPrice,&putPrice);
	*call=callPrice;
	*put=putPrice;
}
