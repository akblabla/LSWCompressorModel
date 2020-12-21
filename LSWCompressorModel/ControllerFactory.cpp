/*
 * ControllerFactory.cpp
 *
 *  Created on: 11 Dec 2020
 *      Author: akbla
 */

#include "ControllerFactory.h"
#include "SoftwareCompressStrategy.h"
#include "SoftwareDecompressStrategy.h"

Controller ControllerFactory::createController(){
    SoftwareCompressStrategy* compressStrategyPtr = new SoftwareCompressStrategy;
    SoftwareDecompressStrategy* decompressStrategyPtr = new SoftwareDecompressStrategy;
    Controller controller(compressStrategyPtr, decompressStrategyPtr);
    return controller;
}
