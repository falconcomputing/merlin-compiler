/*----------------------------------------------------------------------------
*
* Author:   Liang Ma (liang-ma@polito.it)
*
*----------------------------------------------------------------------------
*/
#ifndef __BARRIERDATA_H__
#define __BARRIERDATA_H__

#include "../common/defTypes.h"

class barrierData
{
public:
	data_t upBarrier;
	data_t downBarrier;

	barrierData(data_t,data_t);
	barrierData(const barrierData&);
	void print()const;
	bool checkRange(data_t)const;
};

#endif
