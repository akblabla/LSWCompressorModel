/*
 * Controller.h
 *
 *  Created on: 20 Nov 2020
 *      Author: akbla
 */

#pragma once
#include <string>
#include "PopFrontQueue.h"
class iController {
public:
	virtual void compress(std::string s) = 0;
	virtual void decompress(std::string s) = 0;
	virtual void print(std::string s) = 0;
	virtual void subscribe(PopFrontQueue<std::string>& observer) = 0;
};