/*
 * iDecompressStrategy.h
 *
 *  Created on: 10 Dec 2020
 *      Author: akbla
 */
#ifndef SRC_IDECOMPRESSSTRATEGY_H_
#define SRC_IDECOMPRESSSTRATEGY_H_
#include "iAccess.h"

class iDecompressStrategy {
public:
	virtual int decompress(iAccess& src, iAccess& dst) = 0;
};

#endif /* SRC_IDECOMPRESSSTRATEGY_H_ */
