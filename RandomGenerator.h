#ifndef __RANDOMGENERATOR_H__
#define __RANDOMGENERATOR_H__

#include "MPRNG.h"

class RandomGenerator
{
  public:
	MPRNG generator;
	static RandomGenerator& getInstance()
	{
		static RandomGenerator instance;
		return instance;
	}
};

#endif
