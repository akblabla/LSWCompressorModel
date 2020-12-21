/*
 * iCompressStrategy.h
 *
 *  Created on: 10 Dec 2020
 *      Author: akbla
 */

#ifndef SRC_ICOMPRESSSTRATEGY_H_
#define SRC_ICOMPRESSSTRATEGY_H_
#include "iAccess.h"
class iCompressStrategy {
public:
	virtual int compress(iAccess& src, iAccess& dst) = 0;
};

#endif /* SRC_ICOMPRESSSTRATEGY_H_ */
