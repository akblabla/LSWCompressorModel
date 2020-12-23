/*
 * Controller.cpp
 *
 *  Created on: 20 Nov 2020
 *      Author: akbla
 */
#include <iostream>
#include "Controller.h"
#include <fstream>
Controller::Controller(iCompressStrategy* compressStrategyPtrParam,iDecompressStrategy* decompressStrategyPtrParam) {
	_compressStrategyPtr = compressStrategyPtrParam;
	_decompressStrategyPtr = decompressStrategyPtrParam;
}
void Controller::compress(std::string s){
	if (s.find_first_of(' ') != std::string::npos) {
		print("Command requires only 1 parameter.\n");
		return;
	}
	std::ifstream src(s, std::ifstream::in | std::ifstream::binary);

	if (!src.is_open()) {
		print("Failed to open file " +s+"\n");
		return;
	}
	std::string dstFileName = s + ".lsw";
	std::ofstream dst(dstFileName, std::ofstream::out | std::ofstream::binary);
	if (!dst.is_open()) {
		print("Failed to open file " + dstFileName + "\n");
		src.close();
		return;
	}
	print("Compressing file: " + s + "\n");
	if (_compressStrategyPtr->compress(src, dst) != 0) {
		print("Failed to compress file " + dstFileName + "\n");
		src.close();
		dst.close();
		return;
	}
	src.close();
	dst.close();
}
void Controller::decompress(std::string s){
	if (s.find_first_of(' ') != std::string::npos) {
		print("Command requires only 1 parameter.\n");
		return;
	}
	std::string dstFileName;
	dstFileName.assign(s, 0, s.find_last_of('.'));
	std::string dstFileType;
	dstFileType.assign(s, s.find_last_of('.')+1, SIZE_MAX);
	if (dstFileType != "lsw") {
		print("File is not in .lsw file.\n");
		return;
	}
	std::ifstream src(s, std::ifstream::in | std::ifstream::binary);
	if (!src.is_open()) {
		print("Failed to open file " + s + "\n");
		return;
	}
	std::ofstream dst(dstFileName, std::ofstream::out | std::ofstream::binary);
	if (!dst.is_open()) {
		print("Failed to open file " + dstFileName + ".lsw\n");
		src.close();
		return;
	}
	print("Decompressing file: " + s + "\n");
	if (_decompressStrategyPtr->decompress(src, dst) != 0) {
		print("Failed to decompress file " + dstFileName + "\n");
		src.close();
		dst.close();
		return;
	}
	src.close();
	dst.close();
}
void Controller::print(std::string s){
	_splitter.pushAll(s);
}
void Controller::subscribe(PopFrontQueue<std::string>& queue){
	_splitter.subscribe(queue);
}

Controller::~Controller() {
}

