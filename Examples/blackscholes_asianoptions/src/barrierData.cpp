/*----------------------------------------------------------------------------
*
* Author:   Liang Ma (liang-ma@polito.it)
*
*----------------------------------------------------------------------------
*/

#include "barrierData.h"
#ifdef __CLIANG__
#include <iostream>
using namespace std;
#endif
barrierData::barrierData(data_t upBarrier, data_t downBarrier)
{
	if(upBarrier<downBarrier)
	{
		this->upBarrier=0;
		this->downBarrier=0;
	}
	else
	{
		this->upBarrier=upBarrier;
		this->downBarrier=downBarrier;
	}
}

barrierData::barrierData(const barrierData& data)
{
	this->upBarrier=data.upBarrier;
	this->downBarrier=data.downBarrier;
}

bool barrierData::checkRange(data_t stockPrice)const
{
	return (stockPrice>=downBarrier)&&(stockPrice<=upBarrier);
}

#ifdef __CLIANG__
void barrierData::print()const
{
	cout<<"downBarrier="<<downBarrier<<' '
			<<"upBarrier="<<upBarrier<<endl;
}
#endif
