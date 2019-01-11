/*----------------------------------------------------------------------------
*
* Author:   Liang Ma (liang-ma@polito.it)
*
*----------------------------------------------------------------------------
*/

#include "volatilityData.h"
volData::volData(data_t expect,
					data_t kappa,
					data_t variance,
					data_t initValue,
					data_t correlation)
{
	this->expect=expect;
	this->kappa=kappa;
	this->variance=variance;
	this->initValue=initValue;
	this->correlation=correlation;
}

volData::volData(const volData& data)
{
	this->expect=data.expect;
	this->kappa=data.kappa;
	this->variance=data.variance;
	this->initValue=data.initValue;
	this->correlation=data.correlation;
}


data_t volData::truncFun1(data_t x)
{
	return x;
}
data_t volData::truncFun2(data_t x)
{
	return fmax(x,0);
}
data_t volData::truncFun3(data_t x)
{
	return fmax(x,0);
}

#ifdef __CLIANG__
using namespace std;
void volData::print()const
{
	cout<<"expect:"<<expect<<' '
			<<"variance:"<<variance<<' '
			<<"initValue:"<<initValue<<' '
			<<"correlation:"<<correlation<<endl;
}
#endif
