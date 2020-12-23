/*
 * iDecompressStrategy.h
 *
 *  Created on: 10 Dec 2020
 *      Author: akbla
 */
#ifndef SRC_IDECOMPRESSSTRATEGY_H_
#define SRC_IDECOMPRESSSTRATEGY_H_
#include <istream>
#include <ostream>

class iDecompressStrategy {
public:
	virtual int decompress(std::istream& src, std::ostream& dst) = 0;
};

#endif /* SRC_IDECOMPRESSSTRATEGY_H_ */
