/*
 * Controller.cpp
 *
 *  Created on: 20 Nov 2020
 *      Author: akbla
 */
#include <iostream>
#include "Controller.h"
#include "FileAccess.h"
Controller::Controller(iCompressStrategy* compressStrategyPtrParam,iDecompressStrategy* decompressStrategyPtrParam) {
	_compressStrategyPtr = compressStrategyPtrParam;
	_decompressStrategyPtr = decompressStrategyPtrParam;
}
void Controller::compress(std::string s){
	if (s.find_first_of(' ') != std::string::npos) {
		print("Command requires only 1 parameter.\n");
		return;
	}
	auto src = FileAccess(s,"rb");
	if (!src.isOpen()) {
		print("Failed to open file " +s+"\n");
		return;
	}
	std::string dstFileName = s + ".lsw";
	auto dst = FileAccess(dstFileName, "wb+");
	if (!dst.isOpen()) {
		print("Failed to open file " + dstFileName + "\n");
		return;
	}
	print("Compressing file: " + s + "\n");
	if (_compressStrategyPtr->compress(src, dst) != 0) {
		print("Failed to compress file " + dstFileName + "\n");
		return;
	}
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
	auto src = FileAccess(s, "rb");
	if (!src.isOpen()) {
		print("Failed to open file " + s + "\n");
		return;
	}
	auto dst = FileAccess(dstFileName, "wb+");
	if (!dst.isOpen()) {
		print("Failed to open file " + dstFileName + ".lsw\n");
		return;
	}
	print("Decompressing file: " + s + "\n");
	if (_decompressStrategyPtr->decompress(src, dst) != 0) {
		print("Failed to decompress file " + dstFileName + "\n");
		return;
	}

}
void Controller::print(std::string s){
	_splitter.pushAll(s);
}
void Controller::subscribe(PopFrontQueue<std::string>& queue){
	_splitter.subscribe(queue);
}

Controller::~Controller() {
}

