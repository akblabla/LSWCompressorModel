/*
 * Controller.h
 *
 *  Created on: 20 Nov 2020
 *      Author: akbla
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_
#include <string>
#include "Splitter.h"
#include "iDecompressStrategy.h"
#include "iCompressStrategy.h"
#include "iController.h"
class Controller : iController {
public:
	Controller(iCompressStrategy*,iDecompressStrategy*);
	void compress(std::string s);
	void decompress(std::string s);
	void print(std::string s);
	void subscribe(PopFrontQueue<std::string>& queue);
	virtual ~Controller();
private:
	Splitter _splitter;
	iCompressStrategy *_compressStrategyPtr;
	iDecompressStrategy *_decompressStrategyPtr;
};

#endif /* SRC_CONTROLLER_H_ */
