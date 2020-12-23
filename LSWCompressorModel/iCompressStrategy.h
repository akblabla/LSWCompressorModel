/*
 * iCompressStrategy.h
 *
 *  Created on: 10 Dec 2020
 *      Author: akbla
 */

#ifndef SRC_ICOMPRESSSTRATEGY_H_
#define SRC_ICOMPRESSSTRATEGY_H_
#include <istream>
#include <ostream>
class iCompressStrategy {
public:
	virtual int compress(std::istream& src, std::ostream& dst) = 0;
};

#endif /* SRC_ICOMPRESSSTRATEGY_H_ */
