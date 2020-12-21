/*
 * Subject.cpp
 *
 *  Created on: 20 Nov 2020
 *      Author: akbla
 */

#include "Splitter.h"

Splitter::Splitter() {
	// TODO Auto-generated constructor stub

}

void Splitter::pushAll(std::string msg){
	for (auto const& i : _queues){
		i->push(msg);
	}
}
void Splitter::subscribe(PopFrontQueue<std::string>& queue){
	_queues.push_front(&queue);
}

Splitter::~Splitter() {
	// TODO Auto-generated destructor stub
}

