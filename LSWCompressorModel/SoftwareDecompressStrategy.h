#pragma once
#include "iDecompressStrategy.h"
class SoftwareDecompressStrategy :
	public iDecompressStrategy
{
public:
	SoftwareDecompressStrategy();
	int decompress(iAccess& src, iAccess& dst);
};

