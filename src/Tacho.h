
#ifndef __TACHO_H_
#define __TACHO_H_

namespace std {}
using namespace std;

#include "H_Graphics.h"

class Tacho
{
public:
	Tacho();
	Tacho(REAL RedLine);
	~Tacho();
	void draw(REAL Revs);
private:
	int CompiledList;
	REAL MyRedLine;
};

#endif //__TACHO_H_
