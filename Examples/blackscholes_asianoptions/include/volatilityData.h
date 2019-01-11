/*----------------------------------------------------------------------------
*
* Author:   Liang Ma (liang-ma@polito.it)
*
*----------------------------------------------------------------------------
*/
#ifndef __VOLDATA_H__
#define __VOLDATA_H__

#include "defTypes.h"

class volData
{
public:
	data_t expect;
	data_t kappa;
	data_t variance;
	data_t initValue;
	data_t correlation;

	volData(data_t, data_t,data_t,data_t,data_t);
	volData(const volData&);
	void print()const;
	static data_t truncFun1(data_t);
	static data_t truncFun2(data_t);
	static data_t truncFun3(data_t);
};

#endif
