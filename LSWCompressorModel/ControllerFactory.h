/*
 * ControllerFactory.h
 *
 *  Created on: 11 Dec 2020
 *      Author: akbla
 */

#ifndef SRC_CONTROLLERFACTORY_H_
#define SRC_CONTROLLERFACTORY_H_

#include "Controller.h"

class ControllerFactory {
public:
	static Controller createController();
};

#endif /* SRC_CONTROLLERFACTORY_H_ */
