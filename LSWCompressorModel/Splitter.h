/*
 * Subject.h
 *
 *  Created on: 20 Nov 2020
 *      Author: akbla
 */

#ifndef SRC_SPLITTER_H_
#define SRC_SPLITTER_H_
#include "PopFrontQueue.h"
#include <string>
#include <list>
class Splitter {
public:
	Splitter();
	void pushAll(std::string msg);
	void subscribe(PopFrontQueue<std::string>& splitter);
	virtual ~Splitter();
private:
	std::list<PopFrontQueue<std::string>*> _queues;
};

#endif /* SRC_SPLITTER_H_ */
